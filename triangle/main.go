package main

import (
	"fmt"
	"triangle/domain"
)

func main() {
	points := "abcdefghijk"
	lines := []string{"abh", "acgi", "adfj", "aek", "bcde", "hgfe", "hijk"}

	matches := domain.CountTriangles(points, lines)
	fmt.Println("counting triangles result: ")
	fmt.Println("num of triangles: ", len(matches))
	fmt.Println("detail of triangles: ", matches)
}
