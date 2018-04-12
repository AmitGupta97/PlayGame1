
#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<string.h>
pthread_t t,t1;
pthread_mutex_t l;
typedef struct
{
char name[10];
float time;
int priority;
}detail;
void *Student()
{
pthread_mutex_lock(&l);
printf("Student you can play till 6.00hr \n");
printf("Student playing\n");
sleep(2);
pthread_mutex_unlock(&l);
printf("Student played now next turn\n");
}
void *Faculty()
{
pthread_mutex_lock(&l);
printf("Faculty you can play till 8.00hr \n",time);
printf("Faculty playing\n");
sleep(2);
pthread_mutex_unlock(&l);
printf("Faculty played next turn\n");
}
void *Staff()
{
pthread_mutex_lock(&l);
printf("Staff you can play till you want \n",time);
printf("Staff playing\n");
sleep(2);
pthread_mutex_unlock(&l);
printf("Staff played next turn\n");
}
void *Enter()
{
int n;
detail d[100],t;
printf("enter number of person want to play a game\n");
scanf("%d",&n);
printf("\n\nenter the person who want to play game with their arrival time in 24 hour format\n");
printf("priority of Student is 1 \n priority of Faculty is 2 \n priority of Staff is 3\n");
for(int i=0;i<n;i++)
{
scanf("%s",d[i].name);
scanf("%f",&d[i].time);
scanf("%d",&d[i].priority);
}
for(int i=0;i<n;i++)
{
for(int j=0;j<n-i;j++)
{
if(d[j].priority<d[j+1].priority)
{
t=d[j];
d[j]=d[j+1];
d[j+1]=t;
}
else if(d[j].priority==d[j+1].priority)
{
if(d[j].time>d[j+1].time)
{
t=d[j];
d[j]=d[j+1];
d[j+1]=t;
}
}
}
}
for(int i=0;i<n;i++)
{
if(strcmp(d[i].name,"Student")==0)
{
if(d[i].time>=22.00 || d[i].time<=6.00)
{
printf("\n\nFrom %.2fhr,",d[i].time);
pthread_create(&t1,NULL,Student,NULL);
pthread_join(t1,NULL);
}
else
{
printf("\n\n%s,you are not allowed to play as your arrival %.2fhr time is different from the scheduled one \n",d[i].name,d[i].time);
}
}
else if(strcmp(d[i].name,"Faculty")==0)
{
if(d[i].time>=17.00 || d[i].time<=8.00)
{
printf("\n\nFrom %.2fhr,",d[i].time);
pthread_create(&t1,NULL,Faculty,NULL);
pthread_join(t1,NULL);
}
else
printf("\n\n%s,you are not allowed to play as your arrival %.2fhr time is different from the scheduled one \n",d[i].name,d[i].time);
}
else if(strcmp(d[i].name,"Staff")==0)
{
printf("\n\nFrom %.2fhr,",d[i].time);
pthread_create(&t1,NULL,Staff,NULL);
pthread_join(t1,NULL);
}
else
printf("\n\n%s you don't have access to games\n",d[i].name);
}
pthread_exit(NULL);
}
int main()
{
pthread_create(&t,NULL,Enter,NULL);
pthread_join(t,NULL);
}

