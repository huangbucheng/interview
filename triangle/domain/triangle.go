package domain

import (
	"strings"
)

func CountTriangles(points string, lines []string) []string {
	// 3 points make a triangle, get all subsets with 3 points
	var threePointsSets []string
	var triangles []string
	threePointsSets = SubSets(points, 3)

	// testify a susnet with 3 points is triangle:
	// 1. each 2 points is connected (in one line)
	// 2. all 3 points not in one line
	for _, threePoints := range threePointsSets {
		isConnected := IsConnected(threePoints, lines)
		if !isConnected {
			continue
		}
		if InAnyLine(threePoints, lines) == true {
			continue
		}

		// fmt.Println(threePoints)
		triangles = append(triangles, threePoints)
	}

	return triangles
}

//SubSets: list all subsets with size elements from a set
func SubSets(fullSet string, size int) []string {
	var subSets []string
	if len(fullSet) == 0 || size > len(fullSet) {
		return subSets
	}

	if size == 1 {
		for _, ch := range fullSet {
			subSets = append(subSets, string(ch))
		}
		return subSets
	}

	// subsets with first element
	aSets := SubSets(fullSet[1:], size-1)
	for _, aSet := range aSets {
		subSets = append(subSets, string(fullSet[0])+aSet)
	}
	// subsets without first element
	bSets := SubSets(fullSet[1:], size)
	subSets = append(subSets, bSets...)
	return subSets
}

//IsConnected: is each 2 points connected
func IsConnected(points string, lines []string) bool {
	if len(points) < 2 || len(lines) == 0 {
		return false
	}
	twoPointsSets := SubSets(points, 2)
	for _, twoPoints := range twoPointsSets {
		if InAnyLine(twoPoints, lines) == false {
			return false
		}
	}
	return true
}

//InAnyLine: is all points in one line
func InAnyLine(points string, lines []string) bool {
	for _, line := range lines {
		if IsInLine(points, line) {
			return true
		}
	}
	return false
}

//IsInLine: is all points in one line
func IsInLine(points string, line string) bool {
	if len(points) == 0 || len(line) == 0 {
		return false
	}
	if len(points) > len(line) {
		return false
	}
	for _, point := range points {
		if strings.IndexRune(line, point) == -1 {
			return false
		}
	}
	return true
}
