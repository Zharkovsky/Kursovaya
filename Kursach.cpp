#include<iostream>
#include<cstdlib>
#include "cmath"
#define HASHTAB_SIZE 128
using namespace std;

struct listnode {
    int key;
    struct listnode *next;
};
struct listnode *hashtab[HASHTAB_SIZE];

unsigned int hashtab_hash(int key)     //хэш-функция
{
    float A = 0.618033;                            
    int hashCode = HASHTAB_SIZE * fmod (key * A, 1);
    return hashCode;
}

void hashtab_init(struct listnode **hashtab)  //инициализация хэш-таблицы
{
    for (int i = 0; i < HASHTAB_SIZE; i++)
        hashtab[i] = NULL;
}

bool hashtab_lookup(struct listnode **hashtab, int key)  //поиск значения в хэш-таблице 
{
    int index = hashtab_hash(key);
    for (struct listnode *node = hashtab[index]; node != NULL; node = node->next) 
        if (node->key == key)
            return true; 
            
    return false;
}

bool hashtab_add(struct listnode **hashtab, int key) //добавление в хэш-таблицу
{
    struct listnode *node = new listnode;
    int index = hashtab_hash(key);
    
    // добавление в начало списка
    if (node != NULL && !hashtab_lookup(hashtab, key) ) 
	{
        node->key = key;
        node->next = hashtab[index];
        hashtab[index] = node;
        
        return true;
    }
	    
    return false;
}

bool hashtab_delete(struct listnode **hashtab, int key) //удаление хэш-таблицы 
{
    int index = hashtab_hash(key);
    struct listnode *node = hashtab[index];
    
    //case 0 element
    if(node == NULL) return false;
    
    //case 1 element
    if(node->key == key)
    {
    	struct listnode *temp = node;
    	node = node->next;
    	hashtab[index] = node;
    	temp->next = NULL;
    	delete temp;
    	
    	return true;
	}
	
	//case n elements
	while(node)
	{
		if(node->next->key == key)
		{
			struct listnode *temp = node->next;
			node->next = (node)->next->next;
			temp->next = NULL;
			delete temp;
			
			return true;
		}
		
		node = node->next;
	}
	
	return false;
}

void Clear(struct listnode **hashtab) //очистка хэш-таблицы
{
    for(int i = 0; i < HASHTAB_SIZE; i++)
    {
    	listnode *head = hashtab[i];
    	
    	if (head != NULL)
    	{
    		listnode *prev = NULL;
    		while (head) {
            	prev = head;
            	head = head->next;
            	prev->next = NULL;
            	delete prev;
        	}        	
    	}
    	
    	hashtab[i] = head;
	}
}

bool Show(struct listnode **hashtab)  //элементы хеш-таблицы
{
  bool flag=false;
  listnode *node;
  for (int i = 0; i < HASHTAB_SIZE; i++)
    if(hashtab[i]!=NULL) 
    {
     flag=true;
     node=hashtab[i];
     while(node)
      {
       cout<<node->key<<endl;
       node=node->next;
      }
    }
    
  return flag;
}
   
 	
	

int main()
{
	hashtab_init(hashtab);
	bool flag = true;
	
	cout << "Commands:" << endl 
	<< "1.Add number to the hash" << endl
    << "2.Lookup all information"<<endl
	<< "3.Delete number" << endl
	<< "4.Show all numbers(are ordered on a hash)" << endl 
	<< "5.Clear hashtable" << endl 
	<< "6.End the program" << endl;
          	

	int command;
	while(1)
	{
		cout << endl << "Enter the command: ";
		cin >> command;
		if(command<1 || command>6) 
		 cout<<"Command isn't found";
		switch(command)
		{
			case 1:{
    			cout << "Enter the number: ";
    			int key;
    			cin >> key;
    			flag = hashtab_add(hashtab, key);
    			if(!flag)
    			{
    				cout << "This number already exist" << endl;
				}
    			else cout << "Your key is added" << endl;
				break;
			}
			case 2:{
				cout << "Enter the number: ";
				int key;
				cin >> key;
		        flag = hashtab_lookup(hashtab, key);
		        if(flag)
				{
					cout << " Key: " << key << endl;
				    cout << " Hash: " << hashtab_hash(key) << endl;	
				} 
				else cout << "Not found" << endl;
				break;
			}
			case 3:{
				cout << "Enter number: ";
				int key;
				cin >> key;
				flag = hashtab_delete(hashtab,key);
				if (flag)
					cout << "Your key is deleted" << endl;
				else
					cout << "Your key isn`t founded" << endl;
				break;
			}
			case 4:{
				if(!(Show(hashtab))) cout<<"Hash-table is empty";
				break;
			}
			case 5:{
				Clear(hashtab);
				break;
			}
			case 6:{
				return 0;
				break;
			}
		}
	}
	
	Clear(hashtab);
    return 0;
}
