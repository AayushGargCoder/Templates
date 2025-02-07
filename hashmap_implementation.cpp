#include<iostream>
using namespace std;
template<typename T>
class node{
    public:
    string key;
    T value;
    node<T>* next;
    node(string key,T value){
        this->key=key;
        this->value=value;
        next=NULL;
    }
};
template<typename T>
class map{
    node<T> **bucket_array;
    int buck_size;
    int count;
    int hash_code(string key){
        int p=1;
        int hash_ans=0;
        for(int i=key.size()-1;i>=0;i--){
            hash_ans+=key[i]*p;
            p*=37;
            hash_ans%=buck_size;
            p%=buck_size;
        }
        return hash_ans % buck_size;
    }
    void rehash(){
        node<T> ** temp=bucket_array;
			bucket_array=new node<T>*[2*buck_size];
			for(int i=0;i<2*buck_size;i++){
				bucket_array[i]=NULL;
			}
			int oldbucket=buck_size;
			buck_size*=2;
			count=0;
			for(int i=0;i<oldbucket;i++){
				node<T> *head=temp[i];
				while(head!=NULL){
                    //string key=head->key;
                    //T value=head->value;
					insert(head->key,head->value);
					head=head->next;
				}
			}
			for(int i=0;i<oldbucket;i++){
				delete temp[i];
			}
			delete []temp;
    }
    public:
    map(int size){
        bucket_array=new node<T>*[size];
        for(int i=0;i<size;i++){
            bucket_array[i]=NULL;
        }
        buck_size=size;
        count=0;
    }
    ~map(){
        for(int i=0;i<buck_size;i++){
            delete bucket_array[i];
        }
        delete []bucket_array;
    }
    void insert(string key,T value){
        int index=hash_code(key);
        node<T> *head=bucket_array[index];
        while(head!=NULL){
            if(head->key==key){
                head->value=value;
                return;
            }
            head=head->next;
        }
        head=bucket_array[index];
        node<T> *newNode=new node<T>(key,value);
        newNode->next=head;
        bucket_array[index]=newNode;
        count++;
        double loadfactor=(1.0*count)/buck_size;
        if(loadfactor>0.7){
            rehash();
        }
    }
    T erase(string key){
        int index=hash_code(key);
        node<T> *head=bucket_array[index];
        node<T> *pre=NULL;
        T value;
        while(head!=NULL){
            if(head->key==key){
                if(pre==NULL){
                    bucket_array[index]=head->next;
                }
                else{
                pre->next=head->next;
                }
                value=head->value;
                head->next=NULL;
                delete head;
                count--;
                return value;
            }
            pre=head;
            head=head->next;
        }
        return 0;
    }
    double getloadfactor(){
		return (1.0*count)/buck_size;
	}
};
int main(){
	map<int> m(5);
	for(int i=0;i<15;i++){
		char c='0'+i;
		string ans="abc";
		ans+=c;
		int value=i+1;
		m.insert(ans,value);
        //cout<<m.getloadfactor()<<endl;
	}
    cout<<m.erase("abc1")<<" ";
    cout<<m.erase("abc2")<<" ";
    cout<<m.erase("xyz")<<" ";
}