#include<iostream>
using namespace std;

void sort(int *a,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
}

void sort(char *a,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                int t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
}

void sort(float *a,int n)
{
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(a[j]>a[j+1])
            {
                float t=a[j];
                a[j]=a[j+1];
                a[j+1]=t;
            }
        }
    }
}





int main()
{
    int a[100];
    char b[100];
    float c[100]; 
    int n;
    int c1;
    cout<<"Enter the option \n1.Character\n2.Integer\n3.Floating number\n";
    cin>>c1;
    if(c1==1)
    {
        cout<<"Enter the no.of elements:";
        cin>>n;
        cout<<"Enter the elements:";
        for(int i=0;i<n;i++)
        {
            cin>>b[i];
        }
        sort(b,n);
        cout<<"The sorted elements:";
        for(int i=0;i<n;i++)
            cout<<b[i]<<' ';
        cout<<endl;
    }
    else if(c1==2)
    {
        cout<<"Enter the no.of elements:";
        cin>>n;
        cout<<"Enter the elements:";
        for(int i=0;i<n;i++)
        {
            cin>>a[i];
        }
        sort(a,n);
        cout<<"The sorted elements:";
        for(int i=0;i<n;i++)
            cout<<a[i]<<' ';
        cout<<endl;

    }
    else if(c1==3)
    {
        cout<<"Enter the no.of elements:";
        cin>>n;
        cout<<"Enter the elements:";
        for(int i=0;i<n;i++)
        {
            cin>>c[i];
        }
        sort(c,n);
        cout<<"The sorted elements:";
        for(int i=0;i<n;i++)
            cout<<c[i]<<' ';
        cout<<endl;

    }
}