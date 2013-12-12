#undef TXB_PASS_STRUCT
#undef STRUCT
#undef STRUCT_INHERIT
#undef ATTR
#undef ATTR_NAME
#undef ATTR_PRIVATE
#undef TEXT
#undef CHILD
#undef INHERIT

#define TXB_PASS_XML
#define STRUCT(TYPE) void TXB_binding( TYPE* str, TiXmlElement* xmle, bool m)
#define STRUCT_INHERIT(TYPE, ...) void TXB_binding( TYPE* str, TiXmlElement* xmle, bool m)
#define ATTR(X,HOLDER) TXB_attr_bind( xmle, m, &str-> HOLDER, #HOLDER)
#define ATTR_NAME(X,HOLDER,NAME) TXB_attr_bind( xmle, m, &str-> HOLDER, NAME)
#define ATTR_PRIVATE(X,Y)  
#define TEXT(X,HOLDER) TXB_text_bind( xmle, m, &str-> HOLDER)
#define CHILD(CHILD,HOLDER) TXB_ele_bind<CHILD>( xmle, m, &str-> HOLDER, #CHILD)
#define INHERIT(X) TXB_binding( (X*)str,xmle,m)
