#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"../Model/Model.h"

const char* detectOS() {
    #ifdef _WIN32
    return "Windows 32-bit";
    #elif _WIN64
    return "Windows 64-bit";
    #elif __APPLE__ || __MACH__
    return "Mac OSX";
    #elif __linux__
    return "Linux";
    #elif __FreeBSD__
    return "FreeBSD";
    #elif __unix || __unix__
    return "Unix";
    #else
    return "Other";
    #endif
}

void outputTime(){
    char output[255] = "";
    time_t now;
    struct tm *timeInfo;
    printf("%s\n", asctime(localtime(&now)));

DishNode *createDish(Dish d){
    DishNode *newDish = (DishNode*)malloc(sizeof(DishNode));
    strcpy(newDish->d.dishName, d.dishName);
    newDish->d.price = d.price;
    newDish->d.quantity = d.quantity;
    newDish->next = newDish->prev = NULL;
    return newDish;
}

void pushHead(Dish newDish){
    DishNode *temp = createDish(newDish);
    if(dishHead == NULL){
        dishHead = dishTail = temp;
    } else {
        temp->next = dishHead;
        dishHead->prev = temp;
        dishHead = temp;
    }
}

void pushTail(Dish newDish){
    DishNode *temp = createDish(newDish);
    if(dishHead == NULL){
        dishHead = dishTail = NULL;
    } else {
        temp->prev = dishTail;
        dishTail->next = temp;
        dishTail = temp;
    }
}

void pushMid(Dish newDish){
    if(dishHead == NULL){
        dishHead = dishTail = createDish(newDish); 
    } else if (strcmp(newDish.dishName, dishHead->d.dishName) <= 0){
        pushHead(newDish);
    } else if (strcmp(newDish.dishName, dishTail->d.dishName) >= 0){
        pushTail(newDish);
    } else {
        dishCurr = dishHead;
        while(dishCurr->next && strcmp(newDish.dishName, dishCurr->next->d.dishName) > 0){
            dishCurr = dishCurr->next;
        }
        DishNode *temp = createDish(newDish);
        dishCurr->next->prev = temp;
        temp->next = dishCurr->next;
        dishCurr->next = temp;
        temp->prev = dishCurr;
    }
}

bool checkDishUnique(char *dishName){
    if(dishHead){
        dishCurr = dishHead;
        while(dishCurr && strcmp(dishCurr->d.dishName, dishName) != 0){
            dishCurr = dishCurr->next;
        }
        if(dishCurr == NULL){
            return false;
        }
        else{
            return true;
        }
    }
}

bool checkLowerCase(char *dishName){
    for(int i = 0; dishName[i] != '\0'; i++){
        if(!(dishName[i] >= 'a' && dishName[i] <= 'z') && dishName[i] != ' '){
            return false;
        }
    }
    return true;
}

bool checkName(char *str){
    for(int i = 0; str[i] != '\0'; i++){
        if((!(str[i] <= 'Z' && str[i] >= 'A') && !(str[i] <= 'z' && str[i] >= 'a'))){
            return false;
        }
    }
    return true;
}

int validateNumberInput(){
    int input = -1;
    do{
        printf(">> ");
        scanf("%d", &input);        
        getchar();
    }while(input < 1 || input > 8);
    if(input == 8){
        input = -1;
    }
    return input;
}

void addDish(){
    bool valid = true;
    Dish newDish;
    do{
        valid = true;
        printf("Insert the name of dish [Lowercase letters]: ");
        scanf("%[^\n]", newDish.dishName);
        getchar();
        valid = checkLowerCase(newDish.dishName);
        valid = !checkDishUnique(newDish.dishName);
    } while(valid == false);

    do{
        valid = true;
        printf("Insert the price of the dish [1000..50000]: ");
        scanf("%d", &newDish.price);
        getchar();
        if(newDish.price < 1000 || newDish.price > 50000){
            valid = false;
        }
    } while(valid == false);

    int dishQty;
    do{
        valid = true;
        printf("Insert the quantity of the dish [1..999]: ");
        scanf("%d", &newDish.quantity);
        getchar();
        if(newDish.quantity < 1 || newDish.quantity > 999){
            valid = false;
        }
    } while(valid == false);
    typeOfDish++;
    pushMid(newDish);
}

void outputMenu(){
    int numberPad = 3;
    int namePad = 15;
    int qtyPad = 10;
    int pricePad = 10;
    int titlePad = 10;
    char pad[39];
    char line[39];
    for(int i = 0; i < 39; i++){
        pad[i] = ' ';
        line[i] = '=';
    }
    printf("%.*.s\n", titlePad, titlePad, pad, "Bude\'s Menu");
    printf("%s\n", line);
    printf("No.       Name       Quantity    Price\n");
    dishCurr = dishHead;
    int counter = 1;
    while(dishCurr){
        printf("%-3d %-15s %-4d Rp%-5d\n", counter, dishCurr->d.dishName, dishCurr->d.quantity, dishCurr->d.price);
        dishCurr = dishCurr->next;
        counter++; 
    }
}

void popHead(){
    if(dishHead == NULL){
        return;
    } else if(dishHead == dishTail){
        free(dishHead);
        dishHead = dishTail = NULL;
    } else {
        DishNode *newDishHead = dishHead->next;
        newDishHead->prev = NULL;
        free(dishHead);
        dishHead = NULL;
        dishHead = newDishHead;
        return;
    }
}

void popTail(){
    if(dishHead == NULL){
        return;
    } else if(dishHead == dishTail){
        free(dishHead);
        dishHead = dishTail = NULL;
    } else {
        DishNode *newDishTail = dishTail->prev;
        newDishTail->next = NULL;
        free(dishTail);
        dishTail = NULL;
        dishTail = newDishTail;
        return;
    }
}

bool removeDish(char *dishName){
    if(dishHead == NULL){
        printf("There's no dish\n");
        return false;
    } else if (strcmp(dishHead->d.dishName, dishName) == 0){
        printf("sampe sini\n");
        popHead();
        return true;
    } else if (strcmp(dishTail->d.dishName, dishName) == 0){
        popTail();
        return true;
    } else {
        dishCurr = dishHead;
        while(dishCurr && strcmp(dishCurr->d.dishName, dishName) != 0){
            dishCurr = dishCurr->next;
        }
        if(dishCurr == NULL){
            return false;
        } else {
            dishCurr->prev->next = dishCurr->next;
            dishCurr->next->prev = dishCurr->prev;
            free(dishCurr);
            dishCurr = NULL;
            return true;
        }
    }
}

int hash(char *str){
    long long int total = 0;
    for(int i = 0; str[i] != '\0'; i++){
        if(str[i] >= 'A' || str[i] <= 'Z'){
            total += str[i] - 'A';
        } else if (str[i] >= 'a' || str[i] <= 'z'){
            total += str[i] - 'a';
        }
    }
    return total % SIZE;
}

void pushHeadPerson(Dish newDish, Person *currPerson){
    DishNode *temp = createDish(newDish);
    if(currPerson->head == NULL){
        currPerson->head =currPerson->tail = temp;
    } else {
        temp->next = currPerson->head;
        currPerson->head->prev = temp;
        currPerson->head = temp;
    }
}

void pushTailPerson(Dish newDish, Person *currPerson){
    DishNode *temp = createDish(newDish);
    if(currPerson->head == NULL){
        currPerson->head = currPerson->tail = NULL;
    } else {
        temp->prev  = currPerson->tail;
        currPerson->tail->next = temp;
        currPerson->tail = temp;
    }
}

void pushMidPerson(Dish newDish, Person *currPerson){
    if(currPerson->head == NULL){
        currPerson->head = currPerson->tail = createDish(newDish); 
    } else if (strcmp(newDish.dishName, currPerson->head->d.dishName) <= 0){
        pushHeadPerson(newDish, currPerson);
    } else if (strcmp(newDish.dishName, currPerson->tail->d.dishName) >= 0){
        pushTailPerson(newDish, currPerson);
    } else {
        dishCurr = currPerson->head;
        while(dishCurr->next && strcmp(newDish.dishName, dishCurr->next->d.dishName) > 0){
            dishCurr = dishCurr->next;
        }
        DishNode *temp = createDish(newDish);
        dishCurr->next->prev = temp;
        temp->next = dishCurr->next;
        dishCurr->next = temp;
        temp->prev = dishCurr;
    }
}

Person *createNewPerson(char *str){
        Person *newPerson = (Person *)malloc(sizeof(Person));
        strcpy(newPerson->name, str);
        newPerson->head = NULL;
        newPerson->next = NULL;
        return newPerson;
}

int inputHashTable(char *str){
    int index = hash(str);
    Person *temp = createNewPerson(str);
    if(hashHead[index] == NULL){
        hashHead[index] = hashTail[index] = temp;
    } else {
        hashTail[index]->next = temp;
        hashTail[index] = temp;
    }
}

void validateCustomer(){
    char nameInput[255];
    do{
        printf("Insert the customer\'s name [Without space]: ");
        scanf("%[^\n]", nameInput);
        getchar();
    } while(!checkName(nameInput));
    inputHashTable(nameInput);
}

Person *searchTable(char *nameInput){
    int index = hash(nameInput);
    if(hashHead[index] == NULL){
        return NULL;
    } else {
        Person *curr = hashHead[index];
        while(curr && strcmp(nameInput, curr->name) != 0){
            curr = curr->next;
        }
        return curr;
    }
}

Person *findCustomer(char *nameInput){
    do{
        printf("Insert the customer\'s name to be searched: ");
        scanf("%[^\n]", nameInput);
        getchar();
    } while(!checkName(nameInput));
    return searchTable(nameInput);
}

void viewPeople(){
    for(int i = 0; i < SIZE; i++){
        if(hashHead[i]){
            printf("%d. %s\n", i, hashHead[i]->name);
            if(hashHead[i]->next){
                Person *curr = hashHead[i]->next;
                while(curr){
                    printf("%d. %s\n", i, curr->name);
                    curr = curr->next;
                }
            }
        }
    }
}



void order(Person *currPerson){
    int input = -1;
    do{
        printf("Insert the amount of dish: ");
        scanf("%d", &input);
        if(input > typeOfDish){
            printf("There are only %d dishes !\n", typeOfDish);
        }
    } while(input < 1 || input > typeOfDish);

    char dishNameInput[255];
    int dishQty = -1;
    for(int i = 0; i < input; i++){
        printf("[%d] Insert the dish\'s name and quantity: ", i + 1);
        scanf("%[^x]x%d", dishNameInput,& dishQty);
        getchar();
        dishNameInput[strlen(dishNameInput) - 1] = '\0';
        if(!checkLowerCase){
            i--;
        } else {
            if(!checkDishUnique(dishNameInput)) {
                i--;
            } else {
                if(dishQty > dishCurr->d.quantity || dishQty < 1){
                    i--;
                }
                else{
                    dishCurr->d.quantity -= dishQty;
                    Dish personDish;
                    strcpy(personDish.dishName, dishNameInput);
                    personDish.price = dishCurr->d.price;
                    personDish.quantity = dishQty;
                    if(dishCurr->d.quantity <= 0){
                        removeDish(dishCurr->d.dishName);
                    }
                    pushMidPerson(personDish, currPerson);
                }
            }
        }
    }
}

void popHashHead(int index){
    if(hashHead[index] == NULL){
        return;
    } else if(hashHead[index] == hashTail[index]){
        free(hashHead[index]);
        hashHead[index] = hashTail[index] = NULL;
    } else {
        Person *newHead = hashHead[index]->next;
        hashHead[index] = NULL;
        free(hashHead[index]);
        hashHead[index] = newHead;
    }
}

bool validateHash(int input){
    if(hashHead[input]){
        if(hashHead[input]->head){
            printf("%s\n", hashHead[input]->name);
            dishCurr = hashHead[input]->head;
            int total = 0;
            int counter = 0;
            while(dishCurr){
                printf("[%d] %s x%d\n", counter, dishCurr->d.dishName, dishCurr->d.quantity);
                counter++;
                total += (dishCurr->d.price * dishCurr->d.quantity);
                dishCurr = dishCurr->next;
            }
            printf("Total: Rp%d\n", total);
            popHashHead(input);
            return true;
        }
    }
    return false;
}

void pay(){
    int input = -1;
    do{
        printf("Insert the customer\'s index: ");
        scanf("%d", &input);
    } while (!validateHash(input));
    printf("Press enter to continue...\n");
    getchar();  
}

void cls(){
    for(int i = 0; i < 30; i++){
        puts("");
    }
}