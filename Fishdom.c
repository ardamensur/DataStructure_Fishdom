///ARDA MENSUR
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TRUE 1
#define FALSE 0
#define MAX 40

struct node { // datas for each species
    int weight;
    float vertical_length;
    float diagonal_length;
    float cross_length;
    float height;
    float fish_length;
    int day;
    int month;
    int year;
    char city[MAX];
    struct node *next;
};
typedef struct node *Values;

struct species{ // species list
    char Name[MAX];
    struct node* data;
    struct species* next;
};
typedef struct species *Species;



Values create_value(int weight, float vertical_length, float diagonal_length,  float cross_length, float height, float fish_lenght, int day, int month,int year, char city[MAX]); //to create new values
Species create_species(char *name,Species List,Values value);// to create new species list . Yeni yaratır içine gireni de listedekinin sonuna otomatik olarak ekleme yapıyor.
Species makeoradd_species(Values val, Species list, char name[MAX]);
Species initializeFishing(char *filename);
void printStatistic(Species list);
void addfishdata(Species list);
void DeleteFish(Species list,int treshold);
void AddSpeciesList(Species list);
void searchFishData(Species list);
void Save_all(Species list, char *filename);



int main() {
    int exit = FALSE;
    int command;
    char filename[50] = "fishingArchive.txt";
    Species MySpecies=initializeFishing(filename);



    do {
        printf("\n--------------------MENU------------------------------\n");
        printf("1. Add Fish Data\n2. Delete Fish Data\n3. Print Fish Statistics\n4. Search Fish Data\n5. Add Species List\n6. Exit\n");//MENU
        printf("Enter your opinion:");
        scanf("%d", &command);
        fflush(stdin);
        switch (command) {
            case 1: {//Add fish data
                addfishdata(MySpecies);
                break;
            }
            case 2: {//Delete fish data
                int treshold;
                printf("Provide fish weight threshold in grams:");
                scanf("%d",&treshold);
                DeleteFish(MySpecies, treshold);
                break;
            }
            case 3: {//Print fish statistics
                printStatistic(MySpecies);
                break;
            }
            case 4: {//Search fish data
                searchFishData(MySpecies);
                break;
            }
            case 5: {//Add species list
                AddSpeciesList(MySpecies);
                break;
            }
            case 6: {//exit condition.
                Save_all(MySpecies, filename);
                exit = TRUE; // exit condition
                break;
            }
            default:
                printf("You entered wrong command!!! Please try again\n");
        }
        fflush(stdin);
    } while (!exit);

    return 0;
}

Values create_value(int weight, float vertical_length, float diagonal_length,  float cross_length, float height, float fish_lenght ,int day, int month,int year, char city[MAX]) //to create new values
{
    Values new_data=(Values) malloc(sizeof (struct node));
    new_data->weight=weight;
    new_data->vertical_length=vertical_length;
    new_data->diagonal_length=diagonal_length;
    new_data->cross_length=cross_length;
    new_data->height=height;
    new_data->fish_length=fish_lenght;
    new_data->day=day;
    new_data->month=month;
    new_data->year=year;
    strcpy(new_data->city,city);
    new_data->next=NULL;
    return new_data;
}
Species create_species(char *name,Species List,Values value){// to create new species list.it creates a new field and adds the country name to the list it created.
        Species tmp=List;
        while(tmp->next!=NULL)
            tmp=tmp->next;
        Species new = (Species) malloc(sizeof (struct species));
        strcpy(new->Name, name);
        tmp->next=new;
        new->data=value;
        new->next = NULL;
        new->data->next=NULL;
    return List;
}

Species makeoradd_species(Values val, Species list, char name[MAX]){// this function select making or adding new input.
    if(list ==NULL)
    {
        list = (Species) malloc(sizeof (struct species));
        Species tmp=list;
        strcpy(tmp->Name,name);
        list->data=val;
        list->next=NULL;
        list->data->next=NULL;
    }
    else
    {
        Species tmp=list;
        while (tmp->next!=NULL){
            if(strcmp(name,tmp->Name)!=0)// It checks the names. while they are not same it says move forward.
            {
                tmp=tmp->next;
            }
            else
                break;
        }
        Values tmp_val=tmp->data;
        if(strcmp(name,tmp->Name)==0){
            while (tmp_val->next!=NULL)
            {
                tmp_val=tmp_val->next;
            }
            tmp_val->next=val;
            val->next=NULL;
        }
        else//create spec //if names are not equal
            list=create_species(name,list,val);
        }
    return list;
}

Species initializeFishing(char *filename)
{
    FILE *infile = fopen(filename, "r"); //open method for file, I use pointer(filename) instead of txt file name
    Species list_head= NULL;// I create dynamic memory allocation on main so first time list must be empty

    int weight,day,month,year;
    float vertical_length,diagonal_length,cross_length,height,fish_length;
    char city[MAX];
    char name[MAX];
    if (infile == NULL)
    {
        printf("ERROR!!! The file cannot opened!\n");
        exit(1);
    }
    while(fscanf(infile, "%[^;];%d;%f;%f;%f;%f;%f;%d/%d/%d;%[^\n]\n",name, &weight, &vertical_length, &diagonal_length, &cross_length, &height, &fish_length,&day,&month,&year,city)!=EOF)
    {
        Values new_values=NULL;
        new_values= create_value(weight,vertical_length,diagonal_length,cross_length,height,fish_length,day,month,year,city);//This part for my data linked list I create new data.
        list_head= makeoradd_species(new_values, list_head, name);
    }

    printf("File successfully loaded");
    fclose(infile);
    return list_head ;
}

void printStatistic(Species list){
    char name[MAX];
    int total=0;
    printf("Provide the species:");
    scanf("%s", name);
    Species tmp=list;
    do {//to go input name
        if (strcmp(tmp->Name, name) != 0)
            tmp=tmp->next;
        else
            break;
    } while (tmp->next!=NULL);
    Values tmp_val=tmp->data;
    for (;tmp_val!=NULL;tmp_val=tmp_val->next){
        total++;
    }
    printf("The number of available fish data is %d",total);
}

void addfishdata(Species list){// it takes data and add its Species
    char name[MAX];
    int total=0;
    printf("Species:");
    scanf("%s", name);
    Species tmp=list;
    do {//to go input name
        if (strcmp(tmp->Name, name) != 0)
            tmp=tmp->next;
        else
            break;
    } while (tmp->next!=NULL);
    Values tmp_val=tmp->data;
    while (tmp_val->next!=NULL)
        tmp_val=tmp_val->next;
    int weight,day,month,year;
    float vertical_length,diagonal_length,cross_length,height,fish_length;
    char city[MAX];
    printf("Weight of the fish in grams:");
    scanf("%d",&weight);
    printf("Vertical length in CM:");
    scanf("%f",&vertical_length);
    printf("Diagonal length in CM:");
    scanf("%f",&diagonal_length);
    printf("Cross length in CM:");
    scanf("%f",&cross_length);
    printf("Height in CM:");
    scanf("%f",&height);
    printf("Fish Length in CM:");
    scanf("%f",&fish_length);
    printf("Fishing date:");
    scanf("%d/%d/%d",&day,&month,&year);
    printf("City:");
    scanf("%s",city);
    Values new_values= create_value(weight,vertical_length,diagonal_length,cross_length,height,fish_length,day,month,year,city);
    tmp_val->next=new_values;
    if(new_values!=NULL)
        printf("The data has been added, successfully!\n");
}

void AddSpeciesList(Species list){
    char exit = 'N';
    char Species_name[MAX];
    do {
        printf("The new species is:");
        scanf("%s",Species_name);
        printf("Provide the following info:\n");
        int weight,day,month,year;
        float vertical_length,diagonal_length,cross_length,height,fish_length;
        char city[MAX];
        printf("Weight of the fish in grams:");
        scanf("%d",&weight);
        printf("Vertical length in CM:");
        scanf("%f",&vertical_length);
        printf("Diagonal length in CM:");
        scanf("%f",&diagonal_length);
        printf("Cross length in CM:");
        scanf("%f",&cross_length);
        printf("Height in CM:");
        scanf("%f",&height);
        printf("Fish Length in CM:");
        scanf("%f",&fish_length);
        printf("Fishing date:");
        scanf("%d/%d/%d",&day,&month,&year);
        printf("City:");
        scanf("%s",city);
        Values new_values= create_value(weight,vertical_length,diagonal_length,cross_length,height,fish_length,day,month,year,city);
        list=makeoradd_species(new_values,list,Species_name);
        fflush(stdin);
        printf("Do you want to add more fish (Y/N)");
        scanf("%c",&exit);
    } while (exit!='N');
}

void DeleteFish(Species list,int treshold){
    int counter =0;
    Species tmp;
    tmp=list;
    Species deleteSpec;
    Values deleteVal;
    do
    {
        if(tmp->next->data->next==NULL && treshold>tmp->next->data->weight){// if tmp->next has only 1 value and value's weight<treshold
            deleteSpec =tmp->next;
            deleteVal=tmp->next->data;
            tmp->next=tmp->next->next;
            free(deleteVal);
            free(deleteSpec);
            counter++;
        }
        else//if one species contains more than 1 value
        {
            Values tmp_val=tmp->next->data;
            while(tmp_val->next!=NULL) //while after tmp_val != null
            {
                if(tmp_val->next->weight<treshold){//value smaller than treshold
                    deleteVal = tmp_val->next;
                    tmp_val->next=tmp_val->next->next;
                    free(deleteVal);//deleted the val
                    counter++;
                }
                tmp_val=tmp_val->next;
            }
        }
        tmp=tmp->next;
    }while(tmp->next!=NULL);
    printf("\n%d fish data was deleted from your list!!\n",counter);//output
}



void searchFishData(Species list){
    char option;
    printf("Enter your search option  (C for city/M for month):");
    scanf("%c",&option);
    Species tmp=list;
    if(option == 'C'){//city option
        char city[MAX];
        printf("Enter the city name:");
        scanf("%s",city);
        do {
            Values tmpval=tmp->data;
            while (tmpval!=NULL){
                if (city==tmpval->city){
                    printf("%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",tmp->Name,tmpval->weight,tmpval->vertical_length,tmpval->diagonal_length,tmpval->cross_length,tmpval->height,tmpval->fish_length,tmpval->day,tmpval->month,tmpval->year,tmpval->city);
                }
                tmpval=tmpval->next;
            }
            tmp=tmp->next;
        } while (tmp->next!=NULL);

    }
    else if (option=='M')//for month option
    {
        int month;
        do {
        printf("Enter the month number:");
        scanf("%d",&month);
        if (month>12 || month<0)
            printf("You entered wrong number!!\n");
        } while (month>12 || month<0);

        do {
            Values tmpval=tmp->data;
            while (tmpval!=NULL){
                if (month==tmpval->month){
                    printf("%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",tmp->Name,tmpval->weight,tmpval->vertical_length,tmpval->diagonal_length,tmpval->cross_length,tmpval->height,tmpval->fish_length,tmpval->day,tmpval->month,tmpval->year,tmpval->city);
                }
                tmpval=tmpval->next;
            }

            tmp=tmp->next;
        } while (tmp!=NULL);

    }
    else//for wrong input
        printf("You entered wrong option!");
}

void Save_all(Species list,char *filename){ // to save and write txt
    FILE *infile = fopen(filename, "w");
    Species tmp=list;
    do {
        Values tmpval=tmp->data;
        while (tmpval!=NULL) {
            fprintf(infile,"%s;%d;%f;%f;%f;%f;%f;%d/%d/%d;%s\n",tmp->Name,tmpval->weight,tmpval->vertical_length,tmpval->diagonal_length,tmpval->cross_length,tmpval->height,tmpval->fish_length,tmpval->day,tmpval->month,tmpval->year,tmpval->city);//print almak için fakat hatalı değer çekiyor fonksiyon buraya
            tmpval=tmpval->next;
        }
        tmp=tmp->next;
    } while (tmp != NULL);
    fclose(infile);
    printf("The %s has been updated successfully!\n",filename);
}