package main
import (
	"fmt"
	"math/rand"
	"sync"
	"runtime"
	"sync/atomic"
)

type miserOp struct {
	increment int32
	response chan int32
}

type spendthriftOp struct {
	decrement int32
	response chan int32
}

func report(s string, n int32) {
	fmt.Println(s,n)
}

func main() {
	var reportOn bool = false
	var balance int32 = 0
	var decrements int32 = 0
	var increments int32 = 0
	var limit int = 100
	var maxAmt int32 = 4
	var iteration int = 1000
	var wg sync.WaitGroup
	var buffSize int = 2
	deposits  := make(chan* miserOp, buffSize)
	withdrawals := make(chan* spendthriftOp, buffSize)

	go func () {
		select {
		case deposit := <-deposits:
			balance := deposit.increment
			deposit.response <- balance
		case withdrawawal := <-withdrawals:
			balance -= withdrawawal.decrement
			withdrawawal.response <- balance
		}
	}()

	for i := 0; i < limit; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < iteration; j++ {
				amt := rand.Int31n(maxAmt)
				deposit := &miserOp{increment: amt +1, response: make(chan int32)}
				deposits <- deposit
				newBalance  := <-deposit.response

				if reportOn {
					report("Deposit results in ", newBalance)
				}

				atomic.AddInt32(&increments, amt+1)
				runtime.Gosched()
			}
		}()
	}

	for i := 0; i < limit; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < iteration; j++ {
				amt := rand.Int31n(maxAmt)
				withdrawal := &spendthriftOp{decrement: amt +1, response: make(chan int32)}
				withdrawals <- withdrawal
				newBalance := <-withdrawal.response

				if reportOn {
					report("Withdrawal results in ", newBalance)
				}
				atomic.AddInt32(&decrements, amt + 1)
				runtime.Gosched()
			}
		}()
	}

	wg.Wait()
	report("Final balance:       ", balance)
	report("Total increments:       ", increments)
	report("Total decrements:       ", decrements)
	report("Difference in incr and decr::       ", increments - decrements)




}
