struct Dish{
    char dishName[255];
    int price;
    int quantity;
};

struct DishNode{
    Dish d;
    DishNode *next, *prev;
}*dishHead, *dishTail, *dishCurr;

const int SIZE = 100;

struct Person{
    char name[255];
    DishNode *head, *tail;
    Person *next;
} *hashHead[SIZE], *hashTail[SIZE];

int totalDish = 0;
int typeOfDish = 0;