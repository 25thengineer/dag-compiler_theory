#include <iostream>
#include <string>
#include <string.h>
#include <cctype>
#include <algorithm>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <fstream>
#include <ostream>
#include <iomanip>
#include <stack>
#include <list>
#include <map>
#include <sstream>

using namespace std;


ifstream ifile("test.txt");
ofstream ofile("solution.txt");


struct node
{
    int type;
    node *left,*right;
    list<string> signlist;
    string op;
    int Value;
    bool isNumber;
    node()
    {
        type=0;
        left=NULL;
        right=NULL;
        Value=0;
        isNumber=false;
    }
};


map<int,node*> NodeMap;


node *find(string name)
{
    node *tmp;
    map<int,node* >::iterator it;
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        list<string>::iterator i;
        for (i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            if ((*i).compare(name)==0)
                return tmp;
            if(tmp->isNumber)
            {
                if(tmp->Value==atoi(name.c_str()))
                    return tmp;
            }
        }
    }
    
    return NULL;
}

node * create(string name)
{
    node *newnode=new node();
    
    
    ostringstream os;
    os<<"N"<<NodeMap.size();
    //newnode->signlist.push_front(os.str());
    
    if(isdigit(name[0]))
    {
        newnode->isNumber=true;
        newnode->Value=atoi(name.c_str());
        cout<<"Number="<<newnode->Value<<endl;
    }
    else
        newnode->signlist.push_front(name);
    
    //NodeMap.insert(map<int,node*> :: value_type(size,newnode) );
    cout<<"create Name="<<name<<endl;
    return newnode;
    
}


node * findopyz(string op,node *nodey,node *nodez)
{
    
    node *tmp;
    map<int,node* >::iterator it;
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        list<string>::iterator i;
        for (i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            if(tmp->op==op && tmp->left==nodey && tmp->right==nodez)
                return tmp;
        }
    }
    return NULL;
}

//===========


void tuple3(string x,string y,string op,string z)//x:=y op z
{
    node *nodey=NULL,*nodez=NULL,*nodex=NULL;
    node *tmp;
    int numbery,numberz;
    bool botharenumbers=true;
    nodey=find(y);
    nodez=find(z);
    if(nodey!=NULL)
    {
        if(nodey->isNumber==false)
            botharenumbers=false;
        else
            numbery=nodey->Value;
    }
    else
    {
        if(isdigit(y[0])==false)
            botharenumbers=false;
        else
            numbery=atoi(y.c_str());
    }
    if(nodez!=NULL)
    {
        if(nodez->isNumber==false)
            botharenumbers=false;
        else
            numberz=nodez->Value;
    }
    else
    {
        if(isdigit(z[0])==false)
            botharenumbers=false;
        else
            numberz=atoi(z.c_str());
    }
    
    if( botharenumbers )
    {
        
        nodex=create(x);
        if(op=="+")
        {
            nodex->isNumber=true;
            nodex->Value=numbery+numberz;
        }
        if(op=="-")
        {
            nodex->isNumber=true;
            nodex->Value=numbery-numberz;
        }
        if(op=="*")
        {
            nodex->isNumber=true;
            nodex->Value=numbery*numberz;
        }
        if(op=="/")
        {
            nodex->isNumber=true;
            nodex->Value=numbery/numberz;
        }
        
        stringstream os;
        os<<nodex->Value;
        tmp=find(os.str());
        if(tmp!=NULL)
        {
            tmp->signlist.push_back(x);
            return;
        }
        else
        {
            
            NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodex) );
            return;
        }
        
    }
    
    nodey=find(y);
    
    nodez=find(z);
    if(nodey!=NULL && nodez!=NULL)
    {
        nodex=findopyz(op,nodey,nodez);
        if(nodex!=NULL) 
        {
            nodex->signlist.push_back(x);
            return;
        }
        else
        {
            nodex=find(x);
            if(nodex!=NULL)
            {
               
                list<string>::iterator i;
                if(nodex!=NULL)
                {
                    //cout<<"erase"<<x<<endl;
                    for(i=nodex->signlist.begin();i!=nodex->signlist.end();i++)
                        if((*i).compare(x)==0)
                            i=nodex->signlist.erase(i);
                }
            }
            nodex=create(x);
            nodex->op=op;
            nodex->left=nodey;
            nodex->right=nodez;
            NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodex) );
            return;
        }
    }
    else
    {
        if(nodey==NULL)
        {
            nodey=create(y);
            NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodey) );
            
        }
        else
        {
            nodey->signlist.push_back(y);
        }
        if(nodez==NULL)
        {
            nodez=create(z);
            NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodez) );
            
        }
        else
        {
            nodez->signlist.push_back(z);
        }
        
        nodex=find(x);
        if(nodex!=NULL)
        {
            
            list<string>::iterator i;
            if(nodex!=NULL)
            {
                //cout<<"erase"<<x<<endl;
                for(i=nodex->signlist.begin();i!=nodex->signlist.end();i++)
                    if((*i).compare(x)==0)
                        i=nodex->signlist.erase(i);
            }
        }
        
        nodex=create(x);
        nodex->op=op;
        nodex->left=nodey;
        nodex->right=nodez;
        NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodex) );
        
    }
    
}


node * findxopy(string x,string op,node *nodey)
{
    
    
    node *tmp;
    map<int,node* >::iterator it;
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        list<string>::iterator i;
        for (i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            if ((*i).compare(x)==0)
                if(tmp->op==op && tmp->left==nodey && tmp->right==NULL)
                    return tmp;
        }
    }
    return NULL;
}

void tuple2(string x,string op,string y)//x:=op y
{
    node *nodey,*nodex;
    
    
    
    nodey=find(y);
    if(nodey==NULL)
    {
        nodey=create(y);
    }
    else
    {
        nodex=findxopy(x,op,nodey);
        if(nodex!=NULL)
            return;
    }
    
    
    
    list<string>::iterator i;
    nodex=find(x);
    if(nodex!=NULL)
    {
        //cout<<"erase"<<x<<endl;
        for(i=nodex->signlist.begin();i!=nodex->signlist.end();i++)
            if((*i).compare(x)==0)
                nodex->signlist.erase(i);
    }
    
    
    nodex=create(x);
    if(nodey->isNumber==true)
    {
        //cout<<"nodey is number"<<endl;
        
        
        
        if(op=="+")
        {
            nodex->isNumber=true;
            nodex->Value=nodey->Value;
        }
        if(op=="-")
        {
            nodex->isNumber=true;
            nodex->Value=-nodey->Value;
        }
        
        node *tmp;
        stringstream os;
        os<<nodex->Value;
        tmp=find(os.str());
        
        if(tmp!=NULL)
            tmp->signlist.push_back(x);
        else
            NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodex) );
        
        return;
    }
    else
    {
        cout<<"nodey is not number"<<endl;
        nodex->op=op;
        nodex->left=nodey;
        nodex->right=NULL;
        NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodex) );
        NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodey) );
    }
    
    
    
}


void tuple1(string x,string y)//x:=y
{
    node *nodex,*nodey;
    nodey=find(y);
    if(nodey==NULL)
    {
        nodey=create(y);
        NodeMap.insert(map<int,node*> :: value_type(NodeMap.size(),nodey));
    }
    
    
    
    list<string>::iterator i;
    nodex=find(x);
    if(nodex!=NULL)
    {
        //cout<<"erase"<<x<<endl;
        for(i=nodex->signlist.begin();i!=nodex->signlist.end();i++)
            if((*i).compare(x)==0)
                i=nodex->signlist.erase(i);
    }
    
    nodey->signlist.push_back(x);
    
}


void show()
{
    node *tmp;
    string x,y,z,op;
    map<int,node* >::iterator it;
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        
        
        x=tmp->signlist.front();
        
        
        
        op=tmp->op;
        cout<<"op='"<<op<<"'";
        list<string>::iterator i;
        
        for (i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            cout<<*i<<" ";
        }
        if(tmp->isNumber)
            cout<<"Number is "<<tmp->Value;
        cout<<endl;
        
    }
    
    
}


string printnode(node *nodex)
{
    
    string str;
    if(nodex==NULL)
        return str;
    
    if(nodex->isNumber)
    {
        stringstream os;
        
        os<<nodex->Value;
        str=os.str();
    }
    else
    {
        str=nodex->signlist.front();
    }
    return str;
}
void print()
{
    
    string op,x,y,z;
    node *tmp;
    map<int,node* >::iterator it;
    
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        
        
        
        if(tmp->left==NULL && tmp->right==NULL)
        {
            if(tmp->isNumber)
            {
                list<string>::iterator i;
                for(i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
                {
                    cout<<*i<<" = "<<tmp->Value<<endl;
                }
            }
            continue;
        }
        else
        {
            
            if(tmp->right==NULL)
                cout<<printnode(tmp)<<" = "<<tmp->op<<" "<<printnode(tmp->left)<<endl;
            else
            {
                cout<<printnode(tmp)<<" = "<<printnode(tmp->left)<<" "<<tmp->op<<" "<<printnode(tmp->right)<<endl;
            }
        }
        list<string>::iterator i;
        for(i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            if(i==tmp->signlist.begin())
                continue;
            else
                cout<<*i<<"="<<tmp->signlist.front()<<endl;
        }
    }
}

void printtuple()
{
    string op,x,y,z;
    node *tmp;
    map<int,node* >::iterator it;
    
    for(it=NodeMap.begin();it!=NodeMap.end();it++)
    {
        tmp=it->second;
        if(tmp->left==NULL && tmp->right==NULL)
        {
            if(tmp->isNumber)
            {
                list<string>::iterator i;
                for(i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
                {
                    cout<<"("<<setw(4)<<"=,"<<setw(3)<<tmp->Value<<","<<setw(4)<<","<<setw(4)<<*i<<")"<<endl;
                    ofile<<"("<<setw(4)<<"=,"<<setw(3)<<tmp->Value<<","<<setw(4)<<","<<setw(4)<<*i<<")"<<endl;
                }
            }
            continue;
        }
        else
        {
            
            if(tmp->right==NULL)
            {
                cout<<"("<<setw(3)<<tmp->op<<","<<setw(3)<<printnode(tmp->left)<<","<<setw(3)<<printnode(tmp)<<")"<<endl;
                ofile<<"("<<setw(3)<<tmp->op<<","<<setw(3)<<printnode(tmp->left)<<","<<setw(3)<<printnode(tmp)<<")"<<endl;
            }
            else
            {
                cout<<"("<<setw(3)<<tmp->op<<","<<setw(3)<<printnode(tmp->left)<<","<<setw(3)<<printnode(tmp->right)<<","<<setw(4)<<printnode(tmp)<<")"<<endl;
                ofile<<"("<<setw(3)<<tmp->op<<","<<setw(3)<<printnode(tmp->left)<<","<<setw(3)<<printnode(tmp->right)<<","<<setw(4)<<printnode(tmp)<<")"<<endl;
            }
        }
        list<string>::iterator i;
        for(i=tmp->signlist.begin();i!=tmp->signlist.end();i++)
        {
            if(i==tmp->signlist.begin())
                continue;
            else
            {
                cout<<"("<<setw(4)<<"=,"<<setw(3)<<tmp->signlist.front()<<","<<setw(4)<<","<<setw(4)<<*i<<")"<<endl;
                ofile<<"("<<setw(4)<<"=,"<<setw(3)<<tmp->signlist.front()<<","<<setw(4)<<","<<setw(4)<<*i<<")"<<endl;
                
            }
        }
    }
}

int main()
{
    string op="",x="",y="",z="",parameter1="",parameter2="",parameter3="";
    string strLine;
    while(getline(ifile,strLine))
    {
        
        for(int i=0;i<strLine.length();i++)
        {
            if(strLine[i]=='('||strLine[i]==')'||strLine[i]==',')
                strLine[i]=' ';
        }
        stringstream os(strLine);
        os>>op;
        os>>parameter1;
        os>>parameter2;
        os>>parameter3;
      
        if(op=="=")
        {
            x=parameter2;
            y=parameter1;
            cout<<"x="<<x<<",y="<<y<<endl;
            tuple1(x,y);
        }
        else
            if(parameter3=="")
            {
                x=parameter2;
                y=parameter1;
                cout<<"x="<<x<<",y="<<y<<endl;
                tuple2(x,op,y);
            }
            else
                if(parameter3!="")
                {
                    x=parameter3;
                    y=parameter1;
                    z=parameter2;
                    cout<<"x="<<x<<",y="<<y<<",z="<<z<<endl;
                    tuple3(x,y,op,z);
                }
    }
    
    
    
    printtuple();
    print();
    
    
    ifile.close();
    ofile.close();
    return 0;
}
