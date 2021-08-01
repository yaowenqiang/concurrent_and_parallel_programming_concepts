package main
import(
	"fmt"
	"math/rand"
	"runtime"
	"sync"
	"sync/atomic"
)

func report(s string, n int32) {
	fmt.Println(s,n)
}

func main() {
	var balance int32 = 0
	var lock = &sync.Mutex{}
	var increments int32 = 0
	var decrements int32 = 0
	var goroutineCount int = 100
	var maxAmt int32 = 5
	var iterations int = 1000
	var wg sync.WaitGroup

	for i := 0; i < goroutineCount; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				incr := rand.Int31n(maxAmt) + 1
				lock.Lock()
				balance += incr
				lock.Unlock()
				//report("Despositing   ", incr)
				atomic.AddInt32(&increments, incr)
				runtime.Gosched()
			}
		}()
	}

	for i := 0; i < goroutineCount; i++ {
		wg.Add(1)
		go func() {
			defer wg.Done()
			for j := 0; j < iterations; j++ {
				decr := rand.Int31n(maxAmt) + 1
				lock.Lock()
				balance -= decr
				lock.Unlock()
				//report("Despositing   ", incr)
				atomic.AddInt32(&decrements, decr)
				runtime.Gosched()
			}
		}()

	}

	wg.Wait()
	report("Final balance:               ", balance)
	report("Total increments:            ", increments)
	report("Final decrements:            ", decrements)
	report("Difference in incr and decr: ", increments - decrements)
}
