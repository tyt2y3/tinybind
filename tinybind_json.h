#undef TXB_PASS_STRUCT
#undef TXB_PASS_XML
#undef STRUCT
#undef STRUCT_INHERIT
#undef ATTR
#undef ATTR_NAME
#undef ATTR_PRIVATE
#undef TEXT
#undef CHILD
#undef INHERIT

#define TXB_PASS_JSON
#define STRUCT(TYPE) bool TXB_binding( TYPE* str, cJSON* json, bool m)
#define STRUCT_INHERIT(TYPE, ...) bool TXB_binding( TYPE* str, cJSON* json, bool m)
#define ATTR(X,HOLDER) TXB_attr_bind( json, m, &str-> HOLDER, #HOLDER)
#define ATTR_NAME(X,HOLDER,NAME) TXB_attr_bind( json, m, &str-> HOLDER, NAME)
#define ATTR_PRIVATE(X,Y)  
#define TEXT(X,HOLDER) TXB_text_bind( json, m, &str-> HOLDER)
#define CHILD(CHILD,HOLDER) TXB_ele_bind<CHILD>( json, m, &str-> HOLDER, #CHILD)
#define INHERIT(X) TXB_binding( (X*)str,json,m)
