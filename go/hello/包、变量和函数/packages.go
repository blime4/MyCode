package main

import (
	"fmt"
	"math/rand"
	"time"
)

func main() {
	fmt.Println("My favorite number is ",rand.Intn(15))
	
	for i:=0; i<10;i++ {
		r:=rand.New(rand.NewSource(time.Now().UnixNano()))
		fmt.Printf("%d ",r.Int31())
	}
}