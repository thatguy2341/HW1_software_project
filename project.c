#include <stdio.h>
#include <stdlib.h>


# include <stdio.h>
# include <stdlib.h>

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
    struct vector point;
    struct vector sum;
    int points_assigned;
}
int main(int argc, char **argv)
{

    struct vector *head_vec, *curr_vec, *next_vec;
    struct cord *head_cord, *curr_cord, *next_cord;
    int i, j, rows = 0, cols;
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
    create_clusters();

    for(int i=0;i<iter;i++){

        distance();
        int has_changed update_clusters(clusters,head_vec,epsilon);
        if(has_changed==0){break;}
    }

}
    //2
    struct vector* create_clusters(){

    struct vector *clusters=malloc(sizeof(struct vector*)*k);
    

    }

    //3 compute point distance from every point and update points index;
    void update_points(struct vector* clusters,struct vector* head_vec){
        struct vector* current;
        current=head_vec;
        while(current!=NULL){
            int min;
            int current_cluster=current->cluster_index;
            int next_cluster=current_cluster;
            for(int i=0;i<k;i++){
                int 
                int temp=distance(current, &clusters[i]);
                if(temp<min){   
                    min=temp;
                    next_cluster=i;
                }
            //update sum and counter of the clusters;
        }

    }
    }
    //4
    int  update_clusters(struct vector* clusters,double epsilon){

        return 0;
    }

    move point();
    //5 distance between points
    double distance(struct vector* x,struct vector* y){

            return distance;
    }

 