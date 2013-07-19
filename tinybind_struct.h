#define TXB_PASS_STRUCT
#define STRUCT(TYPE) struct TYPE
#define STRUCT_INHERIT(TYPE, ...) struct TYPE : __VA_ARGS__
#define ATTR(X,Y) X Y
#define ATTR_NAME(X,Y,NAME) X Y
#define ATTR_PRIVATE(X,Y) X Y
#define TEXT(X,Y) X Y
#define CHILD(X,Y) vector<X> Y
#define INHERIT(X) 
