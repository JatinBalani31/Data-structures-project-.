#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int member_number=0;
int trainer_number=0;
int covid_protocol[15];

typedef struct trainer_node {
    int trainer_ID;
    char name[20];
    int age;
    int remuneration;
	char program[20]; 	
	int slots_booked[15];									//6 am to 9 pm we get 14 hours so accordingly slot booking
	int availability;
	
	int t_height;
	struct trainer_node* left;
	struct trainer_node* right;
}trainer;

typedef struct Node {
    int member_ID;
    char name[20];
    int age;
    char gender[10];
	char program[20];
	int time_preffered;
	int trainer_pref_id; 
	int slot_booking_index;
    char timestamp[6];
    
    int height;
	struct Node* left;
    struct Node* right;
    struct trainer_node* trainer;
}member;

struct trainer_rem {
    int trainer_ID;
    char name[20];
    int age;
    int remuneration;
	char program[20]; 	
	int slots_booked[15];									//6 am to 9 pm we get 14 hours so accordingly slot booking
	int availability;
	
	int t_height;
	struct trainer_rem* left;
	struct trainer_rem* right;
};
typedef struct schedule_slot
{
	int trainer_id ;
	int member_id;
	char time_stamp[20];
	char program[20] ;
	int time;
	
	int height;
	struct trainer_node* trainer;
	struct schedule_slot* left;
	struct schedule_slot* right;
}Slot;

int max(int a, int b)
{
    return (a > b)? a : b;									//Max of a and b 
}

int height(struct Node *N)									// A function to get the height of the tree
{
    if(N == NULL)
        return 0;    
    return 1+max(height(N->left),height(N->right));
}

struct Node *rightRotate(struct Node *y)					//Right rotation function
{
    struct Node *x = y->left;
    struct Node *T2 = x->right;
 
    x->right = y;											//Perform rotation
    y->left = T2;
    
    y->height = height(y);									//Update heights
    x->height = height(x);
    
	return x;								     			//Return new root
}
 
struct Node *leftRotate(struct Node *x)						//Left rotation function 
{
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;								   			 //Perform Rotation
    x->right = T2;

    x->height = height(x);					     			//Update heights
    y->height = height(y);

    return y;												// Return new root
}

int getBalance(struct Node *N)										//Getting the balance factor of N 
{
    if (N == NULL)
        return 0;
    return (height(N->left) - height(N->right));
}

struct Node* newNode(struct Node* new_member)
{
    struct Node* node = new_member;						
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0;  									// new node is initially added at leaf
    return(node);
}
struct Node* insert(struct Node* node, struct Node* new_member)
{
	int key =new_member->member_ID;
	
	if (node == NULL)
        return(newNode(new_member)); 
    
	if (key < node->member_ID)
        node->left  = insert(node->left, new_member);
    else if (key > node->member_ID)
        node->right = insert(node->right, new_member);				 	//Equal keys are not input (member ids) and also not allowed in BST
 	else 
        return node;
  
    node->height = height(node);								//Update height of this ancestor node
    
	int balance = getBalance(node);
    
	if (balance > 1 && key < node->left->member_ID)				// Left Left Case
        return rightRotate(node);
 
    if (balance < -1 && key > node->right->member_ID)		    // Right Right Case
        return leftRotate(node);
 
    if (balance > 1 &&  key > node->left->member_ID)			// Left Right Case
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && key < node->right->member_ID)			// Right Left Case
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}
 
struct Node* Add_member(struct Node* root)
{	
	struct Node *new_member= (struct Node*)malloc(sizeof(struct Node));
    int key;
    
	member_number++;
	new_member->member_ID = member_number + 1000;			//Assigning random member id 
    key = new_member -> member_ID;
	
	printf("Name :");
	scanf("%s",&new_member->name);
    printf("Age :");
	scanf("%d",&new_member->age);
    printf("Gender(M/F/O):");
	scanf("%s",&new_member->gender);
    printf("Program(YOGA/CARDIO/ZUMBA/WEIGHT_LIFTING):");
    scanf("%s",&new_member->program);
	
    new_member->left = NULL;
	new_member->right = NULL;
    
    printf("________________________________________________________________________________________________________");
    printf("\nMember_Id:%d\nName :%s\nAge:%d\nGender:%s\nProgram Enrolled :%s ",new_member->member_ID,new_member->name,new_member->age,new_member->gender,new_member->program);
	
	if(root == NULL)
    {
       root = new_member;
       printf("\n\t\t The member has been added successfully");
       return root;
    } 
    
    root = insert(root , new_member );
	
	printf("\n\t\t The new member has been added successfully");
    return root;						  			 /* return the (unchanged) node pointer */  
}

int t_height(struct trainer_node *T)									// A function to get the height of the tree
{
    if (T == NULL)
        return 0;
    return 1+max(t_height(T->left), t_height(T->right));
}

struct trainer_node *right_TRotate(struct trainer_node *y)	//Right rotation function
{
    struct trainer_node *x = y->left;
    struct trainer_node *T2 = x->right;
 
    x->right = y;													//Perform rotation
    y->left = T2;
    
    y->t_height = t_height(y);										//Update heights
    x->t_height = t_height(x);
	return x;								 		    			//Return new root
}

struct trainer_node *left_TRotate(struct trainer_node *x)			//Left rotation function 
{
    struct trainer_node *y = x->right;
    struct trainer_node *T2 = y->left;

    y->left = x;								   					//Perform Rotation
    x->right = T2;
	
    x->t_height = t_height(x);					     				//Update t_heights
    y->t_height = t_height(y);

    return y;														// Return new root
}

int get_TBalance(struct trainer_node *T)							//Getting the balance factor of T
{
    if (T == NULL)
        return 0;
    return t_height(T->left) - t_height(T->right);
}

struct trainer_node* newtrainer_node(struct trainer_node* new_trainer)
{
    struct trainer_node* node = new_trainer;						
    node->left   = NULL;
    node->right  = NULL;
    node->t_height = 0;  									// new node is initially added at leaf
    return(node);
}

struct trainer_node* insert_trainer(struct trainer_node* node, struct trainer_node* new_trainer)
{
	int key = new_trainer->trainer_ID;
	
	if (node == NULL)
        return(newtrainer_node(new_trainer));
        
    if (key < node->trainer_ID)
        node->left  = insert_trainer(node->left, new_trainer);
    else if (key > node->trainer_ID)
        node->right = insert_trainer(node->right, new_trainer);				//Equal keys are not input (trainer ids) and also not allowed in BST
 
    node->t_height = t_height(node);								//Update height of this ancestor node
    
	int balance = get_TBalance(node);
    
	if (balance > 1 && key < node->left->t_height)					// Left Left Case
        return right_TRotate(node);
 
    if (balance < -1 && key > node->right->t_height)		  	    // Right Right Case
        return left_TRotate(node);
 
    if (balance > 1 &&  key > node->left->t_height)					// Left Right Case
    {
        node->left =  left_TRotate(node->left);
        return right_TRotate(node);
    }

    if (balance < -1 && key < node->right->t_height)				// Right Left Case
    {
        node->right = right_TRotate(node->right);
        return left_TRotate(node);
    }
    return node;
}

struct trainer_node* Add_trainer(struct trainer_node *t_root)
{
	struct trainer_node* new_trainer=(struct trainer_node*)malloc(sizeof(struct trainer_node));
    
	trainer_number++;
    new_trainer->trainer_ID = trainer_number + 5000;		//Assigning random trainer id 
   	int key =new_trainer->trainer_ID;
    
	printf("Name :");
	scanf("%s",&new_trainer->name);
    printf("Age :");
	scanf("%d",&new_trainer->age);
    printf("Renumeration:");
	scanf("%d",&new_trainer->remuneration);
    printf("Program teaching(YOGA/CARDIO/ZUMBA/WEIGHT LIFTING)(If multiple , write with ','):");
    scanf("%s",&new_trainer->program);
    printf("Available(1) / Not available(0):");
    scanf("%d",&new_trainer->availability);
    printf("________________________________________________________________________________________________________");
    printf("\nTrainer_Id:%d\nName :%s\nAge:%d\nRemuneration:%d\nProgram Teaching :%s\n Availability:%d ",new_trainer->trainer_ID,new_trainer->name,new_trainer->age,new_trainer->remuneration,new_trainer->program,new_trainer->availability);
	
	if (t_root == NULL)
    {
       t_root = new_trainer;
       printf("\n\t\t The trainer has been added successfully");
       return t_root;
    } 
    
	t_root = insert_trainer( t_root ,new_trainer);
   
    printf("\n\t\t The new trainer has been added successfully");
    printf("________________________________________________________________________________________________________");
	return t_root;
}

int check_print=0;
int check_print_f(struct Node *root)
{	
	check_print=1;
	if(root==NULL)
		{
			printf("\n List is empty , please input a member first \n");
			printf("_______________________________________________________________________________________________\n");
			return 0;		
		}
	else
		return 1;	
}

void print_member_list(struct Node *root)
{	
	struct Node* current = root;
	int c=1 ;
	
	if(check_print==0) 
		c=check_print_f(root);
	
	if(c==1)
	{
		if(current==NULL)
			return;
		else					//Recursive print Inorder function to print the member list 
		{
				print_member_list(current->left);
				
				printf("_______________________________________________________________________________________________\n");
				printf("\nMember_Id:%d\nName :%s\nAge:%d\nGender:%s\nProgram Enrolled :%s \n",current->member_ID,current->name,current->age,current->gender,current->program);
				printf("_______________________________________________________________________________________________\n");
				
				print_member_list(current->right);
		}
	}
}

int check_tprint=0;
int check_tprint_f(struct trainer_node *t_root)
{	
	check_tprint=1;
	if(t_root==NULL)
		{
			printf("\n List is empty , please input a trainer first \n");
			printf("_______________________________________________________________________________________________\n");
			return 0;		
		}
	else
		return 1;	
}

void print_trainer_list(struct trainer_node *t_root)
{	
	struct trainer_node* current_trainer = t_root;
	int c;
	
	if(check_tprint==0) 
			c=check_tprint_f(t_root);
	if(c==1)
	{
		if(current_trainer==NULL)
			return;
		else							//Recursive print Inorder function to print the trainer list 
		{
				print_trainer_list(current_trainer->left);
				
				printf("_______________________________________________________________________________________________\n");
				printf("\nTrainer_Id:%d\nName :%s\nAge:%d\nRemuneration:%d\nProgram Teaching :%s \n",current_trainer->trainer_ID,current_trainer->name,current_trainer->age,current_trainer->remuneration,current_trainer->program);
				printf("_______________________________________________________________________________________________\n");
				
				print_trainer_list(current_trainer->right);
		}
	}
}

struct Node * minValueNode(struct Node* node)
{
    struct Node* current = node;
 
    while (current->left != NULL)											// loop down to find the leftmost leaf to get he min value node 
        current = current -> left;
 
    return current;
}

struct Node* delete_member(struct Node* root , int key)				//Returns the root of  the modified subtree
{
    if (root == NULL)
        return root;

    if( key < root->member_ID )											// If the key to be deleted is smaller than the root's key, then it lies in left subtree
        root->left = delete_member(root->left, key);
 
    else if( key > root->member_ID )										// If the key to be deleted is greater than the root's key, then it lies in right subtree
        root->right = delete_member(root->right, key);
 	else
    {
        if( (root->left == NULL) || (root->right == NULL) )			// node with only one child or no child
        {
            struct Node *temp = root->left ? root->left : root->right;

            if (temp == NULL)										// No child case
            {
                temp = root;
                root = NULL;
            }
            else 													// One child case
             *root = *temp; 										// Copy the contents of the non-empty child
            free(temp);
        }
        else
        {
            struct Node* temp = minValueNode(root->right);				// Node with two children: Get the inorder successor (smallest in the right subtree)
           
		    root->member_ID = temp->member_ID;										// Copy the inorder successor's data to this node
            root->right = delete_member(root->right, temp->member_ID);			// Delete the inorder successor
        }
    }
 
    if (root == NULL)																//If the tree had only one node then return
      return root;
 
    root->height = 1 + max(height(root->left), height(root->right));				//Updating the height of the tree
 
    int balance = getBalance(root);													//Getting balance factor to get whether node is balanced or not 
 
    // If this node becomes unbalanced, then there are 4 cases
 
    if (balance > 1 && getBalance(root->left) >= 0)									// Left Left Case
        return rightRotate(root);
 
    if (balance > 1 && getBalance(root->left) < 0)									// Left Right Case
    {
        root->left =  leftRotate(root->left);
        return rightRotate(root);
	}
   
    if (balance < -1 && getBalance(root->right) <= 0)							    // Right Right Case
        return leftRotate(root);
 
    if (balance < -1 && getBalance(root->right) > 0)								// Right Left Case
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
 	printf("Member is successfully deleted ");
    return root;
}

struct trainer_node * minValue_TNode(struct trainer_node* t_node)
{
    struct trainer_node* current = t_node;
 
    while (current->left != NULL)											// loop down to find the leftmost leaf to get he min value node 
        current = current -> left;
 
    return current;
}

struct trainer_node* delete_trainer(struct trainer_node* root , int key)	//Returns the root of  the modified subtree
{
    if (root == NULL)
        return root;
	
    if( key < root->trainer_ID )											// If the key to be deleted is smaller than the root's key, then it lies in left subtree
        root->left = delete_trainer(root->left, key);
 
    else if( key > root->trainer_ID )										// If the key to be deleted is greater than the root's key, then it lies in right subtree
        root->right = delete_trainer(root->right, key);
 	else
    {
        if( (root->left == NULL) || (root->right == NULL) )			// t_node with only one child or no child
        {
            struct trainer_node *temp = root->left ? root->left : root->right;

            if (temp == NULL)										// No child case
            {
                temp = root;
                root = NULL;
            }
            else 													// One child case
             *root = *temp; 										// Copy the contents of the non-empty child
            free(temp);
        }
        else
        {
            struct trainer_node* temp = minValue_TNode(root->right);				// Node with two children: Get the inorder successor (smallest in the right subtree)
           
		    root->trainer_ID = temp->trainer_ID;									// Copy the inorder successor's data to this t_node
            root->right = delete_trainer(root->right, temp->trainer_ID);			// Delete the inorder successor
        }
    }
 
    if (root == NULL)																//If the tree had only one t_node then return
      return root;
 
    root->t_height = 1 + max(t_height(root->left), t_height(root->right));				//Updating the height of the tree
 
    int balance = get_TBalance(root);												//Getting balance factor to get whether t_node is balanced or not 
 
    // If this t_node becomes unbalanced, then there are 4 cases
 
    if (balance > 1 && get_TBalance(root->left) >= 0)								 // Left Left Case
        return right_TRotate(root);
 
    if (balance > 1 && get_TBalance(root->left) < 0)							 	// Left Right Case
    {
        root->left =  left_TRotate(root->left);
        return right_TRotate(root);
	}
   
    if (balance < -1 && get_TBalance(root->right) <= 0)							    // Right Right Case
        return left_TRotate(root);
 
    if (balance < -1 && get_TBalance(root->right) > 0)								// Right Left Case
    {
        root->right = right_TRotate(root->right);
        return left_TRotate(root);
    }
 	printf("Trainer is successfully deleted ");
    return root;
}

struct Node* search_member(struct Node* root, int key)
{	
	static int flag_print=0;
		  
	if (root == NULL || root->member_ID == key)						// Base Cases: root is null or key is present at root
       {
       	printf("_______________________________________________________________________________________________\n");
       	printf("\nMember_Id:%d\nName :%s\nAge:%d\nGender:%s\nProgram Enrolled :%s \n",root->member_ID,root->name,root->age,root->gender,root->program);
		printf("_______________________________________________________________________________________________\n");
		flag_print=1; 
	   	return root; 
	   }
    
    if (root->member_ID < key)									    // Key is greater than root's key
       return search_member(root->right, key);
 	 
	if (root->member_ID > key)
    	return search_member(root->left, key);								// Key is smaller than root's key
    
	if(flag_print==0)
		printf("Member with given id doesn't exist");	
			
}

struct trainer_node* search_trainer(struct trainer_node* root, int key)
{	
	static int flag_print=0;
	
    if (root == NULL || root->trainer_ID== key)						// Base Cases: root is null or key is present at root
       {
       	printf("_______________________________________________________________________________________________\n");
   	    printf("\nTrainer_Id:%d\nName :%s\nAge:%d\nRemuneration:%d\nProgram Teaching :%s \n",root->trainer_ID,root->name,root->age,root->remuneration,root->program);
		printf("_______________________________________________________________________________________________\n");
		flag_print=1; 
		return root;
	   }
    
    if (root->trainer_ID < key)									  		  // Key is greater than root's key
       return search_trainer(root->right, key);
 	 
	if (root->trainer_ID > key)
    	return search_trainer(root->left, key);								// Key is smaller than root's key
    
	if(flag_print==0)
		printf("Member with given id doesn't exist");
		
}

void Range_Search(struct Node* root ,int start_key, int end_key)
{	
	
	if ( root==NULL )
      return;
 
   if ( start_key < root->member_ID )
     	Range_Search(root->left, start_key, end_key);										//inorder print with the key range condition
 
   if (	start_key <= root->member_ID && end_key >= root->member_ID )
     {
			printf("_______________________________________________________________________________________________\n");
			printf("\nMember_Id:%d\nName :%s\nAge:%d\nGender:%s\nProgram Enrolled :%s \n",root->member_ID,root->name,root->age,root->gender,root->program);
			printf("_______________________________________________________________________________________________\n");
			
 	 }
   Range_Search(root->right, start_key, end_key);								// Recursively calling the right subtree 
}

struct trainer_node* newtrainer_node_rem(struct trainer_node* new_trainer)
{
    struct trainer_node* node = new_trainer;						
    node->left   = NULL;
    node->right  = NULL;
    node->t_height = 0;  									// new node is initially added at leaf
    return(node);
}

struct trainer_node* insert_trainer_node(struct trainer_node* node, struct trainer_node* new_trainer)
{
	int key = new_trainer->remuneration;
	
	if(node == NULL)
        return(newtrainer_node_rem(new_trainer));
        
    if(key < node->remuneration)
        node->left = insert_trainer_node(node->left, new_trainer);
    else if(key > node->remuneration)
    	node->right = insert_trainer_node(node->right, new_trainer);		//Equal keys are not input (trainer ids) and also not allowed in BST
 
    node->t_height = t_height(node);								//Update height of this ancestor node
    
	int balance = get_TBalance(node);
    
	if (balance > 1 && key < node->left->t_height)					// Left Left Case
        return right_TRotate(node);
 
    if (balance < -1 && key > node->right->t_height)		  	    // Right Right Case
        return left_TRotate(node);
 
    if (balance > 1 &&  key > node->left->t_height)					// Left Right Case
    {
        node->left =  left_TRotate(node->left);
        return right_TRotate(node);
    }

    if (balance < -1 && key < node->right->t_height)				// Right Left Case
    {
        node->right = right_TRotate(node->right);
        return left_TRotate(node);
    }
    return node;
}

struct trainer_node* copy(struct trainer_node* root,struct trainer_node* t_root)
{
	//Taking input from the trainer data and making a avl tree in sorted order of remuneration
	
	struct trainer_node* new_trainer=(struct trainer_node*)malloc(sizeof(struct trainer_node));
	
	//Copying the details from the trainer tree 
	
	strcpy(new_trainer->name,t_root->name);
	new_trainer->age=t_root->age;
	new_trainer->remuneration=t_root->remuneration;
	new_trainer->trainer_ID=t_root->trainer_ID;
	strcpy(new_trainer->program,t_root->program);
	new_trainer->availability=t_root->availability;
	
	return new_trainer;
}

struct trainer_node* copy_rem (struct trainer_node* root,struct trainer_node* t_root)
{
	//Taking input from the trainer data and making a avl tree in sorted order of remuneration
	
	struct trainer_node* new_trainer=(struct trainer_node*)malloc(sizeof(struct trainer_node));
	
	//Copying the details from the trainer tree 
	
	strcpy(new_trainer->name,t_root->name);
	new_trainer->age=t_root->age;
	new_trainer->remuneration=t_root->remuneration;
	new_trainer->trainer_ID=t_root->trainer_ID;
	strcpy(new_trainer->program,t_root->program);
	new_trainer->availability=t_root->availability;
	
	return new_trainer;
}

int print_rem_list(struct trainer_node* root)
{
	struct trainer_node* current_trainer=root;
	
	if(current_trainer==NULL)
		return 0;
	else										//Recursive print Inorder function to print the trainer list 
	{
		print_rem_list(current_trainer->left);
		
		printf("_______________________________________________________________________________________________\n");
		printf("\nRemuneration:%d\nTrainer_Id:%d\nName :%s\nAge:%d\nProgram Teaching :%s \n",current_trainer->remuneration,current_trainer->trainer_ID,current_trainer->name,current_trainer->age,current_trainer->program);
		printf("_______________________________________________________________________________________________\n");
				
		print_rem_list(current_trainer->right);
	}
}

struct trainer_node* sorted_rem_list(struct trainer_node* root,struct trainer_node* t_root)
{
	if(root==NULL)
		return 0;
	else 
	{
		sorted_rem_list(root,t_root->left);
		
		struct trainer_node* node_rem=(struct trainer_node*)malloc(sizeof(struct trainer_node));
		node_rem=copy_rem (root,t_root);
		root = insert_trainer_node(root,node_rem);
		sorted_rem_list(root,t_root->right);
	}
	return root;
}
int print_sorted_remuneration_list(struct trainer_node* root,struct trainer_node* t_root)
{
		if(root==NULL)
		{
			root=copy(root,t_root);
		}
		root=sorted_rem_list(root,t_root);		
		print_rem_list(root);
		
}

void trainer_availability(struct trainer_node* t_root)
{
		if(t_root==NULL)
			return;
		else
		{
			trainer_availability(t_root->left);
			
			printf("\nID:%d\nNAME:%s\n",t_root->trainer_ID,t_root->name);
			scanf("%d",t_root->availability);
			
			trainer_availability(t_root->right);	
		}	
}

int s_height(struct schedule_slot *N)										// A function to get the height of the tree
{
    if(N == NULL)
        return 0;    
    return 1+max(s_height(N->left),s_height(N->right));
}

struct schedule_slot *right_SRotate(struct schedule_slot *y)					//Right rotation function
{
    struct schedule_slot *x = y->left;
    struct schedule_slot *T2 = x->right;
 
    x->right = y;															//Perform rotation
    y->left = T2;
    
    y->height = s_height(y);													//Update heights
    x->height = s_height(x);
    
	return x;								     							//Return new root
}
 
struct schedule_slot *left_SRotate(struct schedule_slot *x)						//Left rotation function 
{
    struct schedule_slot *y = x->right;
    struct schedule_slot *T2 = y->left;

    y->left = x;								   			 //Perform Rotation
    x->right = T2;

    x->height = s_height(x);					     			//Update heights
    y->height = s_height(y);

    return y;												// Return new root
}

int get_SBalance(struct schedule_slot *N)										//Getting the balance factor of N 
{
    if (N == NULL)
        return 0;
    return (s_height(N->left) - s_height(N->right));
}

struct schedule_slot* new_snode(struct schedule_slot* new_member)
{
    struct schedule_slot* node = new_member;						
    node->left   = NULL;
    node->right  = NULL;
    node->height = 0;  									// new node is initially added at leaf
    return(node);
}

struct schedule_slot* insert_slot(struct schedule_slot* node, struct schedule_slot* new_slot)
{
	int key = new_slot->time;
	
	if (node == NULL)
        return(new_snode(new_slot));
        
    if (key < node->time)
        node->left  = insert_slot(node->left, new_slot);
    else if (key > node->time)
        node->right = insert_slot(node->right, new_slot);				//Equal keys are not input (trainer ids) and also not allowed in BST
 
    node->height = s_height(node);								//Update height of this ancestor node
    
	int balance = get_SBalance(node);
    
	if (balance > 1 && key < node->left->height)					// Left Left Case
        return right_SRotate(node);
 
    if (balance < -1 && key > node->right->height)		  	    // Right Right Case
        return left_SRotate(node);
 
    if (balance > 1 &&  key > node->left->height)					// Left Right Case
    {
        node->left =  left_SRotate(node->left);
        return right_SRotate(node);
    }

    if (balance < -1 && key < node->right->height)				// Right Left Case
    {
        node->right = right_SRotate(node->right);
        return left_SRotate(node);
    }
    return node;
}

void print_slot_list(struct schedule_slot *root)
{	
	struct schedule_slot* current = root;
	
		if(current==NULL)
			return;
		else					//Recursive print Inorder function to print the member list 
		{
				print_slot_list(current->left);
				
				printf("_______________________________________________________________________________________________\n");
				printf("\nMember_Id:%d\nTrainer_Id :%d\nTime:%d:00\n\nProgram Enrolled :%s \n",current->member_id,current->trainer_id,current->time,current->program);
				printf("_______________________________________________________________________________________________\n");
				
				print_slot_list(current->right);
		}
}

struct trainer_node* search_trainer_s(struct trainer_node* root, int key)
{	
    if (root == NULL || root->trainer_ID== key)						// Base Cases: root is null or key is present at root
       {
		return root;
	   }
    
    if (root->trainer_ID < key)									  		  // Key is greater than root's key
       return search_trainer(root->right, key);
 	 
	if (root->trainer_ID > key)
    	return search_trainer(root->left, key);								// Key is smaller than root's key

}

struct schedule_slot* Schedule_slot(struct schedule_slot* s_root ,struct Node* root,struct trainer_node* t_root)
{	

	//printf("If the trainer with the given id and name is avaiable enter 1 , if not enter 0 ");
	//trainer_availability(t_root);
	    
	int member_id,c=1;
	
	do{
	  
		printf("\nEnter your member id: ");
		scanf("%d",&member_id);
		struct Node* mptr=search_member(root,member_id);
		if(mptr==NULL)
		{
			printf("Enter valid member id");
			c=0;
		} 
	}while(c=0);
	
	
	struct Node* mptr=search_member(root,member_id);
	struct trainer_node* tptr;
	int time_pref=mptr->time_preffered;
	if(mptr->slot_booking_index!=NULL)
	{
		printf("You can book only one slot per day ");
	}
	else
	{
		do{
	    	printf("Enter your preffered time in 24 hr format (6 - 20): ");
			scanf("%d",&mptr->time_preffered);
			if(mptr->time_preffered<6 || mptr->time_preffered>20)
				{
					printf("Enter starting time from  6 to 20: ");	
					c=0;
				}
			}while(c=0);	
			
			c=1;
			
			do{
			
			printf("Enter your preferred trainer id");
			scanf("%d",&mptr->trainer_pref_id);
			
		
			tptr=search_trainer_s(t_root,mptr->trainer_pref_id);
			if(tptr==NULL)
				{
					printf("Trainer  with input id not found , enter valid trainer id ");
					c=0;
				}
			}while(c=0);	
			
			if(tptr->availability==1)
			{
				if(strstr(tptr->program,mptr->program)!=NULL || strcmp(tptr->program,mptr->program)==0 )					//CHECK PROGRAM 
				{
					if(covid_protocol[(mptr->time_preffered-6)]<=10)														//COVID PROTOCOL
					{
						if((tptr->slots_booked[(mptr->time_preffered - 6)])!=1 )											//SLOT EMPTY CHECK
						{
							mptr->slot_booking_index=1;
							mptr->trainer=tptr;
							tptr->availability=0;
							tptr->slots_booked[(mptr->time_preffered)-6]=1;
							
							struct schedule_slot* new_slot =(struct schedule_slot*)malloc(sizeof(struct schedule_slot));
							new_slot->member_id=mptr->member_ID;
							strcpy(new_slot->program,mptr->program);
							new_slot->time=mptr->time_preffered;
							new_slot->trainer=tptr;
							
							if(s_root== NULL)	
							{
								s_root=new_slot;
								printf("Slot has been booked for the given member at time %d:00 with %s trainer",mptr->time_preffered,tptr->trainer_ID);
							}
							else
							{
								s_root=insert_slot(s_root,new_slot);
								printf("Slot has been booked for the given member at time %d:00 with %s trainer",mptr->time_preffered,tptr->trainer_ID);
							}
						}
						else
						{	
							int flag=1;
							while(flag=1 && time_pref<21)
							{	
								time_pref++;
								if((tptr->slots_booked[(time_pref - 6)])!=1)
									flag=0;
							}	
							if(flag==0)
							{
								mptr->slot_booking_index=1;
								mptr->trainer=tptr;
								tptr->availability=0;
								tptr->slots_booked[(time_pref)-6]=1;
								
								struct schedule_slot* new_slot =(struct schedule_slot*)malloc(sizeof(struct schedule_slot));
								new_slot->member_id=mptr->member_ID;
								strcpy(new_slot->program,mptr->program);
								new_slot->time=time_pref;
								new_slot->trainer=tptr;
								
								if(s_root==NULL)	
								{
									s_root=new_slot;
									printf("Slot has been booked for the given member at time %d:00 with %s trainer",time_pref,tptr->trainer_ID);
								}
								else
								{
									s_root=insert_slot(s_root,new_slot);
									printf("Slot has been booked for the given member at time %d:00 with %s trainer",time_pref,tptr->trainer_ID);
								}
							}
							else
							{
								printf("Trainer is busy all the day ");	
							}
						}		
					}
					else
					{
						printf("\nBookings at this time exceeded the covid protocol");
					}
				}
				else 
				{
					printf("The preffered trainer doesn't teach the program: %s",mptr->program);
				}
			}
			else 
			{
				printf("The preffered trainer is not available");
			}	
	}
	print_slot_list(s_root);
	return s_root;
		
}
	
int main()
{
	int choice,flag=1;	
	struct Node* Member_root = NULL;

	struct trainer_node* Trainer_root = NULL;
	struct trainer_node* sort_rem_root =NULL; 
	struct schedule_slot* slot_root = NULL;

	while(flag==1)
	{
		printf("\t\t Welcome to this program .Strictly give input with CAPSLOCK ON and precise.");
		printf("\n\nSelect your choice:\n1.Add Member\n2.Add trainer\n3.Schedule slot\n4.Print hour wise list()\n5.Delete Member\n6.Delete Trainer\n7.Search member\n8.Search trainer\n9.Print member list\n10.Print trainer list\n11.Print Sorted remuneration list\n12.Range Search ");
		scanf("%d",&choice);

		switch(choice)
		{
			case 1:{
				Member_root=Add_member(Member_root);
				break;
			}
			case 2:{
				Trainer_root=Add_trainer(Trainer_root);
				break;
			}
			case 3:{
				slot_root=Schedule_slot(slot_root,Member_root,Trainer_root);
				break;
			}
		/*	case 4:{
				print_hour_wise_list(&slot_head,&Member_root,&Trainer_root);
				break;
			}
		*/	case 5:{
				int key;
				printf("Enter the member id of the member to be deleted:");
				scanf("%d",&key);
				delete_member(Member_root ,key);
				break;
			}
			case 6:{
				int key;
				printf("Enter the trainer id of the trainer to be deleted:");
				scanf("%d",&key);
				delete_trainer(Trainer_root ,key);
				break;
			}	
			case 7:{ 
				struct Node* location = NULL;
				check_print=0;
				int key;
				printf("Enter the member id to search :");
				scanf("%d",&key);
				location = search_member(Member_root,key);
				break;
			}
			case 8:{
				struct trainer_node* tlocation = NULL;
				check_tprint=0;
				int key;
				printf("Enter the trainer id :");
				scanf("%d",&key);
				tlocation=search_trainer(Trainer_root,key);
				break;
			}
			case 9:{
				print_member_list(Member_root);
				break;
			}
			case 10:{
				print_trainer_list(Trainer_root);
				break;
			}
			case 11:{
				if(Trainer_root==NULL)
					printf("Trainer list is empty ,add a trainer first");
				else	
					print_sorted_remuneration_list(sort_rem_root,Trainer_root);
				break;
			}
		 	case 12:{
		 		
		 		int start_key,end_key;
		 	
				printf("Enter the  starting member id:");
		 		scanf("%d",&start_key);

				printf("Enter the ending member id:");
				scanf("%d",&end_key);

				Range_Search(Member_root ,start_key, end_key);
				break;
			}
			default:printf("Invalid input choice");
			break;
		}
		printf("\n Enter 1 to continue , 0 to quit\n");
		scanf("%d",&flag);
	}
	return 0;
}
	

