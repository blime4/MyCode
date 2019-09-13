package main

import "fmt"

func add(x int,y int) int {
	return x+y
}

func add_2(x ,y int) int {
	return x+y
}

func main() {
	fmt.Println(add(42,13))
	fmt.Println(add(23,45))
}

/*
 当连续两个或多个函数的已命名形参类型相同时，除最后一个类型以外，其它都可以省略。

在本例中，

x int, y int

被缩写为

x, y int
*/