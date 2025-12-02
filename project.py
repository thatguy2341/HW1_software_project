

import sys
import math


def distance();
	
def print_clusters(clusters)

def	 updated_points(points, clusters, clusters_sum):

def updated_clusters(clusters, clusters_sum, epsilon):

def read_points():
	#pts is list of list of floats
	points = []
	all_input = sys.stdun.read.strip()
	lines=all_input.splitlines()

	for line in lines:
		coards_string=line.split(',')
		current_point=[]
		
		for coard in coards_string:
			coard_float=float(coard)
			current_point.append(coard_float)
		points.append(current_point)

	return points

#main function
def kmeans(k: int, iters: int):
	epsilon = 0.001
	points = read_points
	points_num = len(points)

	# all points must have same dimension
	dim = len(points[0])
	
	for p in points:
		if len(p) != dim:
			print("Inconsistent dimensions in input")
			return None
	#contidions for k and iters
	if k <= 1 or k >= points_num:
		print("Incorrect number of clusters!")
		return None
	if iters <= 1 or iters >= 800:
		print("Incorrect maximum iteration!")
		return None

	clusters = points[:k]
	clusters_sum=[[0.0]*dim for x in range(k)]

	for i in range (iters)
		updated_points(points, clusters, clusters_sum)
		diff = updated_clusters(clusters,clusters_sum,epsilon)
		if(diff<epsilon)
			break
	
	print_clusters(clusters)
	return 0


if __name__ == '__main__':
	if len(sys.argv) < 3:
		print("Usage: python project.py <k> <iters>  (points from stdin, one csv row per point)")
		sys.exit(1)

	try:
		k_ = int(sys.argv[1])
		iters_ = int(sys.argv[2])
	except ValueError:
		print("k and iters must be integers")
		return 0
	
	if(k<=1 or k>=counter):
        print("Incorrect number of clusters!")
        return 0
    
    if(iter<=1 or iter>=800):
        print("Incorrect maximum iteration!")
        return 0
    
	kmeans(k, iters)

	return 0
