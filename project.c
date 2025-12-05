#include <stdio.h>
#include <stdlib.h>
#include <math.h>

struct cord
{
    double value;
    struct cord *next;
};
struct vector
{   int cluster_index;
    double current_distance;
    struct vector *next;
    struct cord *cords;
   
};
struct cluster{
    struct vector *point;
    struct vector *sum;
    int points_assigned;
};
int main(int argc, char *argv[])
{   //input reading.
    int k=atoi(argv[1]);
    double epsilon=0.001;
    int iter=atoi(argv[2]);
    //inputfile reader from std_in
    //creating points
    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int counter=0;
    int i=0, j=0 , cols=0;
    double n;
    char c;
    
    
    head_cord = malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;
    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            counter++;
           
            curr_vec->next = malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            head_cord = malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    
    //checking correct input
    if(k<=1||k>=counter){
        printf("Incorrect number of clusters!");
        return 0;
    }
    if(iter<=1||iter>=800){
        printf("Incorrect maximum iteration!");
        return 0;
    }
    //create clusters points
    struct cluster* clusters =  create_clusters(argv[3],k,head_vec);
   //main loop
    
    for(int i=0;i<iter;i++){

        update_points(clusters,head_vec,k);
        double max_changed = update_clusters(clusters,epsilon);
        if(max_changed<epsilon){
            break;
        }
        
    }
    
    print_clusters(clusters,k);
    //free memory
    return 0;
}
    //2 recieve args[2] and for each line create cluster_points and add to clusters
    //guy
    struct cluster* create_clusters(char* cluster_input,int k,struct vector* head_vec){
        struct vector* current=head_vec;
        // Get dimansion of vectors:
        int dim = 0;
        struct cord* curr_cord = current->cords;
        while (curr_cord != NULL) {
            dim++;
            curr_cord = curr_cord->next;
        }

        // Initialize zero vector for sum
        struct vector* zero;

        //need to assign the first k point as clusters
        struct cluster *clusters=(struct cluster*)malloc(sizeof(struct cluster)*k);
        for(int i=0;i<k;i++){
            // Create zero vector:
            zero = create_zero_vector(dim);

            // Take care of clusters:
            clusters[i].point=current;
            clusters[i].sum=zero;
            clusters[i].points_assigned=0;
        }
    }

    struct vector* create_zero_vector(int dim){
        struct vector* zero;
        zero = malloc(sizeof(struct vector));
        struct cord* start_cord = malloc(sizeof(struct cord));
        start_cord->value = 0.0;
        start_cord->next = NULL;
        zero->cords = start_cord;
        struct cord* last_cord = start_cord;
        for (int j = 1; j < dim; j++) {
            struct cord* new_cord = malloc(sizeof(struct cord));
            new_cord->value = 0.0;
            new_cord->next = NULL;
            last_cord->next = new_cord;
            last_cord = new_cord;
        }
        return zero;
    }
    

    
    

    //3 compute point distance from every point and update points index;
    //noam
    void update_points(struct cluster* clusters,struct vector* head_vec, int k){
        struct vector* current;
        current=head_vec;

        while(current!=NULL){
            
            double min=distance(current,clusters[0].point);
        
            int current_cluster=current->cluster_index;
            int next_cluster_index=0;
            //check which cluster is the closest to the point
            for(int i=1;i<k;i++){ 
                double temp=distance(current, clusters[i].point);
                if(temp<min){  
                    min=temp;
                    next_cluster_index=i;
                }
            }
            //update sum and counter of the clusters
            if(current_cluster!=next_cluster_index){
                current->cluster_index=next_cluster_index;
                add_vector(clusters[current_cluster].sum,current,-1);
                add_vector(clusters[next_cluster_index].sum,current,1);
                clusters[current_cluster].points_assigned--;
                clusters[next_cluster_index].points_assigned++;
            }
            //move to next point
            current=current->next;
        }
    }
    //add two vectors from same size of linked list, operation is -1 for subtract 1 for add
    void add_vector(struct vector* base,struct vector* add,int operation){
        
        struct cord *curr_base_cord=base->cords;
        struct cord *curr_add_cord=add->cords;
        
        while(curr_base_cord!=NULL&&curr_add_cord!=NULL){
            curr_base_cord->value+=curr_add_cord->value*(operation);
            curr_base_cord=curr_base_cord->next;
            curr_add_cord=curr_add_cord->next;
            }
        }
    
    //4 update clusters points, and returning the maximum change in points
    //guy
    double  update_clusters(struct cluster* clusters,double epsilon){

        return 0;
    }

    
    //5 distance between points
    //noam
    double distance(struct vector* x,struct vector* y){
        double distance=0;
        double sum_square=0;
        struct cord *x_current_cord=x->cords;
        struct cord *y_current_cord=y->cords;
        while (y_current_cord!=NULL&&x_current_cord!=NULL){
            double diff=(x_current_cord->value)-(y_current_cord->value);
            sum_square+=diff*diff;
            y_current_cord=y_current_cord->next;
            x_current_cord=x_current_cord->next;
        }
        distance=sqrt(sum_square);
        return distance;
    }
    //6 print clusters
    void print_clusters(struct cluster* clusters,int k);

 