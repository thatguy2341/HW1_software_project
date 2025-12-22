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

/* Safe malloc wrapper that checks for allocation failure */
void* safe_malloc(size_t size) {
    void* ptr ;
    ptr = malloc(size);
    while (ptr == NULL)
    {
        ptr = malloc(size);
    }
    return ptr;
}

/* all help function declarations */
/* distance between points */
double distance(struct vector* x,struct vector* y){
        double distance=0;
        double sum_square=0;
        struct cord *y_current_cord;
        struct cord *x_current_cord; 
        x_current_cord = x->cords;
        y_current_cord = y->cords;
        while (y_current_cord!=NULL&&x_current_cord!=NULL){
            double diff=(x_current_cord->value)-(y_current_cord->value);
            sum_square+=diff*diff;
            y_current_cord=y_current_cord->next;
            x_current_cord=x_current_cord->next;
        }
        distance=sqrt(sum_square);
        return distance;
    }
/* add two vectors from same size of linked list, operation is -1 for subtract 1 for add */
void add_vector(struct vector* base,struct vector* add,int operation){
        
        struct cord *curr_base_cord=base->cords;
        struct cord *curr_add_cord=add->cords;
        
        while(curr_base_cord!=NULL&&curr_add_cord!=NULL){
            curr_base_cord->value+=(curr_add_cord->value)*(operation);
            curr_base_cord=curr_base_cord->next;
            curr_add_cord=curr_add_cord->next;
            }
    }
 
struct vector* create_zero_vector(int dim){
        struct vector* zero;
        struct cord* start_cord;
        struct cord* last_cord;
        int j;
        zero = safe_malloc(sizeof(struct vector));
        start_cord = safe_malloc(sizeof(struct cord));
        start_cord->value = 0.0;
        start_cord->next = NULL;
        zero->cords = start_cord;
        last_cord = start_cord;
        for (j = 1; j < dim; j++) {
            struct cord* new_cord = safe_malloc(sizeof(struct cord));
            new_cord->value = 0.0;
            new_cord->next = NULL;
            last_cord->next = new_cord;
            last_cord = new_cord;
        }
        return zero;
    }

struct vector* copy_vector(struct vector* original){
        struct vector* copy = safe_malloc(sizeof(struct vector));
        struct cord* original_cord = original->cords;
        struct cord* copy_cord = safe_malloc(sizeof(struct cord));
        copy->cords = copy_cord;

        while (original_cord != NULL) {
            copy_cord->value = original_cord->value;
            if (original_cord->next != NULL) {
                copy_cord->next = safe_malloc(sizeof(struct cord));
                copy_cord = copy_cord->next;
            } else {
                copy_cord->next = NULL;
            }
            original_cord = original_cord->next;
        }
        return copy;
    } 

    /* 2 recieve args[2] and for each line create cluster_points and add to clusters */
    /* guy */
struct cluster* create_clusters(int k,struct vector* head_vec){
        struct vector* current=head_vec;
        struct cluster *clusters;
            /* Initialize zero vector for sum */
        struct vector* zero;
        int i;
        /* Get dimansion of vectors: */
        int dim = 0;
        struct cord* curr_cord = current->cords;
        while (curr_cord != NULL) {
            dim++;
            curr_cord = curr_cord->next;
        }

        
        /* need to assign the first k point as clusters */
        clusters=(struct cluster*)safe_malloc(sizeof(struct cluster)*k);
        for(i=0;i<k;i++){
            /* Create zero vector: */
            zero = create_zero_vector(dim);

            /* Take care of clusters: */
            clusters[i].point=copy_vector(current);
            clusters[i].sum=zero;
            clusters[i].points_assigned=0;
            current=current->next;
        }
        return clusters;
    }


void update_points(struct cluster* clusters,struct vector* head_vec, int k){
        struct vector* current;
        current=head_vec;

        while(current!=NULL){
            
            double min=distance(current,clusters[0].point);
        
            int current_cluster=current->cluster_index;
            int next_cluster_index=0;
            /* check which cluster is the closest to the point */
            int i;
            for(i=1;i<k;i++){ 
                double temp=distance(current, clusters[i].point);
                if(temp<min){  
                    min=temp;
                    next_cluster_index=i;
                }
            }
            /* only on first iteration when current cluster is -1 */
            if (current_cluster==-1)
            {
                
                current->cluster_index=next_cluster_index;
                add_vector(clusters[next_cluster_index].sum,current,1);
                clusters[next_cluster_index].points_assigned++;
                current=current->next;
                continue;
            }
            
            /* update sum and counter of the clusters */
            if(current_cluster!=next_cluster_index){
                current->cluster_index=next_cluster_index;
                add_vector(clusters[current_cluster].sum,current,-1);
                add_vector(clusters[next_cluster_index].sum,current,1);
                clusters[current_cluster].points_assigned--;
                clusters[next_cluster_index].points_assigned++;
            }
            /* move to next point */
            current=current->next;
        }
    }

    
    /* free vector and cords */
void free_vector(struct vector* vec){
        struct cord* current_cord = vec->cords;
        struct cord* next_cord;
        while (current_cord != NULL) {
            next_cord = current_cord->next;
            free(current_cord);
            current_cord = next_cord;
        }
        free(current_cord);
        free(vec);
    }

/* 4 update clusters points, and returning the maximum change in points */
/* guy */
double  update_clusters(struct cluster* clusters,int k,struct vector* head_vec){
        int i;
        struct cord* sum_cord;
        /* change L for to pointer beacause clusters is an array */
        struct cluster *curr_cluster = &clusters[0];
        double max_change = 0;
        double current_change = 0;
        struct cord* point_cord;
        /*checking for empty clusters and reassigning them*/
        for(i=0;i<k;i++){
            if(clusters[i].points_assigned==0){
                int cluter_index_to_reassign;
                curr_cluster=&clusters[i];
                
                cluter_index_to_reassign = head_vec->cluster_index;
                
                curr_cluster->point=copy_vector(head_vec);
                
                clusters[cluter_index_to_reassign].points_assigned--;
                add_vector(clusters[cluter_index_to_reassign].sum,head_vec,-1);
                
            }
        }
        
        for (i=0; i < k; i++) {
            /* copy point to compare later: */
            struct vector* old_point;
            curr_cluster = &clusters[i];
            /* need to check what we suppose to do if the cluster has no points assigned! */


            
            old_point = copy_vector(curr_cluster->point);

            /* get the sum vector: */
            sum_cord = curr_cluster->sum->cords;
            /* get the cords of the point of the cluser: */
            point_cord = curr_cluster->point->cords;

            while (sum_cord != NULL && point_cord != NULL) {
                double new_value = (sum_cord->value) / (curr_cluster->points_assigned);
                point_cord->value = new_value;

                sum_cord = sum_cord->next;
                point_cord = point_cord->next;
            }

             current_change=distance(old_point, curr_cluster->point);
             if (current_change > max_change) {
                max_change = current_change;
        }
            free_vector(old_point);
            
        }
  
        return max_change;
    }


    /* 6 print clusters */
void print_clusters(struct cluster* clusters, int k) {
    int i;
    for (i = 0; i < k; i++) {
        struct cord* curr = clusters[i].point->cords;

        while (curr != NULL) {
            printf("%.4f", curr->value);
            if (curr->next != NULL) {
                printf(",");
            }
            curr = curr->next;
        }
        printf("\n");
    }
}


/* main function */
int main(int argc, char *argv[])
{   /* input reading. */
    int k, iter;
    double epsilon;
    double max_changed;
    struct vector* next_vec;
    /* inputfile reader from std_in */
    /* creating points */
    struct vector *head_vec, *curr_vec;
    struct cord *head_cord, *curr_cord;
    int counter=0, i;
    /* int i=0, j=0 , cols=0; */
    double n;
    char c;
    struct cluster* clusters;

    iter = 400; /* defualt value */
    epsilon=0.001;
    if (argc == 3){
        iter=atoi(argv[2]);
    }
    else if (argc !=2){
        printf("An Error Has Occurred");
        return 1;
    }
    k=atoi(argv[1]);
    if(k<=0){
        printf("Invalid number of clusters!");
        return 1;
    }
    if(iter<=1||iter>=800){
        printf("Incorrect maximum iteration!");
        return 1;
    }

    head_cord = safe_malloc(sizeof(struct cord));
    curr_cord = head_cord;
    curr_cord->next = NULL;

    head_vec = safe_malloc(sizeof(struct vector));
    curr_vec = head_vec;
    curr_vec->next = NULL;
    head_vec->cluster_index = -1;
    
    while (scanf("%lf%c", &n, &c) == 2)
    {

        if (c == '\n')
        {
            int check;
            curr_cord->value = n;
            curr_vec->cords = head_cord;
            counter++;
           /* check if end of file */
           check=getchar();
           if(check==EOF){
            break;
           }
            ungetc(check,stdin);
            
            curr_vec->next = safe_malloc(sizeof(struct vector));
            curr_vec = curr_vec->next;
            curr_vec->next = NULL;
            curr_vec->cluster_index = -1;
            
            head_cord = safe_malloc(sizeof(struct cord));
            curr_cord = head_cord;
            curr_cord->next = NULL;
            continue;
        }

        curr_cord->value = n;
        curr_cord->next = safe_malloc(sizeof(struct cord));
        curr_cord = curr_cord->next;
        curr_cord->next = NULL;
    }
    
    /* checking correct input */
    if(counter==0){
        printf("An Error Has Occurred");
        return 1;
    }
    if(k>=counter){
        printf("Incorrect number of clusters!");
        return 1;
    }

    /* create clusters points */
    clusters = create_clusters(k,head_vec);
    /* main loop */
    
    for(i=0;i<iter;i++){
        update_points(clusters,head_vec,k);
        max_changed = update_clusters(clusters,k,head_vec);
        if(max_changed<epsilon){
            break;
        }
        
    }
    print_clusters(clusters,k);
    
    /* free memory */
    for (i = 0; i < k; i++)
    {
        free_vector(clusters[i].sum);
        free_vector(clusters[i].point);

    }
    free(clusters);
    curr_vec = head_vec;
    while (curr_vec != NULL)
    {
        next_vec = curr_vec->next;
        free_vector(curr_vec);
        curr_vec = next_vec;
    }
    free(curr_vec);
    return 0;
}




    

