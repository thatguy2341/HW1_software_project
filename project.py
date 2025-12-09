import sys
import math

#compute distance between two vectors.
def distance(vector1, vector2):
	distance =0.0
	for i in range(len(vector1)):
		distance += (vector1[i]-vector2[i])**2
	return math.sqrt(distance)
#print the clusters, each in a row
def print_clusters(clusters):
	for cluster in clusters:
		st=""
		for x in range(len(cluster)):
			if x!=0:
				st+=','
			st+='{0:.4f}'.format(cluster[x])
		print(st)

#asigned each point to her closest cluster, and update clusters_sum and clusters_count if needed
def	 updated_points(points,points_to_clusters, clusters, clusters_sum,clusters_count):
	for t in range(len(points)):
		
		min_dist = distance(points[t], clusters[0])
		closest_cluster = 0

		for i in range(1, len(clusters)):
			dist = distance(points[t], clusters[i])
			if (dist < min_dist):
				min_dist = dist
				closest_cluster = i
		
		before_cluster = points_to_clusters[t]
		points_to_clusters[t] = closest_cluster
		
		#we wont subtruct from sum and count if the point was not assigned before
		if (before_cluster == -1):
			clusters_count[closest_cluster] += 1
			for j in range(len(points[t])):
				clusters_sum[closest_cluster][j] += points[t][j]
		
		if (before_cluster != closest_cluster and before_cluster != -1):
			clusters_count[closest_cluster] += 1
			clusters_count[before_cluster] -= 1
			for j in range(len(points[t])):
				clusters_sum[closest_cluster][j] += points[t][j]
				clusters_sum[before_cluster][j] -= points[t][j]


#update clusters after the recent change in the assigned points,returning the max change in any cluster
def updated_clusters(clusters, clusters_sum,clusters_count, epsilon):
	max_diff = 0.0
	for i in range (len (clusters)):
		new_cluster = [0.0 for x in range(len(clusters[0]))]	
		if clusters_count[i] > 0:
			for j in range(len(clusters[0])):
				new_cluster[j] = clusters_sum[i][j] / clusters_count[i]
		else:
			new_cluster = clusters[i]
		
		diff = distance(clusters[i], new_cluster)
		if diff > max_diff:
			max_diff = diff
		clusters[i] = new_cluster
	return max_diff
#read point from std
def read_points():
	#pts is list of list of floats
	points = []
	all_input = sys.stdin.read().strip()
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
def kmeans(k: int, max_iters: int):
	epsilon = 0.001
	points = read_points()
	points_num = len(points)
	#point in i place in order is assign to cluster points_to_clusters[i]
	points_to_clusters = [-1 for x in range(points_num)]

	# all points must have same dimension
	dim = len(points[0])
	
	for p in points:
		if len(p) != dim:
			print("Inconsistent dimensions in input")
			return 0
	
	if(k<=1 or k>=len(points)):
		print("Incorrect number of clusters!")
		return 0
	
	if(max_iters<=1 or max_iters>=800):
		print("Incorrect maximum iteration!")
		return 0
	#clusters are the first k points
	clusters = points[:k]
	#initialize clusters_sum and clusters_count,updating happens in updated_points
	clusters_sum=[[0.0]*dim for x in range(k)]
	clusters_count=[0 for x in range(k)]
	#main algo loop
	for i in range (max_iters):
		updated_points(points,points_to_clusters, clusters, clusters_sum,clusters_count)
		diff = updated_clusters(clusters,clusters_sum,clusters_count,epsilon)
		if(diff<epsilon):
			break
	#we finish updating, printing the clusters
	print_clusters(clusters)
	return 0


if __name__ == '__main__':
	if len(sys.argv) < 3:
		print("problem with input args")
		sys.exit(1)

	try:
		k = int(sys.argv[1])
		max_iters = int(sys.argv[2])
	except ValueError:
		print("k and iters must be integers")
		sys.exit(1)

	kmeans(k, max_iters)

	sys.exit(0)
