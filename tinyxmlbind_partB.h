#undef STRUCT
#undef STRUCT_INHERIT
#undef ATTR
#undef ATTR_NAME
#undef ATTR_PRIVATE
#undef TEXT
#undef CHILD
#undef INHERIT

#define STRUCT(TYPE) bool TXB_binding( TYPE* str, TiXmlElement* xmle, bool m)
#define STRUCT_INHERIT(TYPE, ...) bool TXB_binding( TYPE* str, TiXmlElement* xmle, bool m)
#define ATTR(X,HOLDER) TXB_attr_bind( xmle, m, &str-> HOLDER, #HOLDER)
#define ATTR_NAME(X,HOLDER,NAME) TXB_attr_bind( xmle, m, &str-> HOLDER, NAME)
#define ATTR_PRIVATE(X,Y)  
#define TEXT(X,HOLDER) TXB_text_bind( xmle, m, &str-> HOLDER)
#define CHILD(CHILD,HOLDER) TXB_ele_bind<CHILD>( xmle, m, &str-> HOLDER, #CHILD)
#define INHERIT(X) TXB_binding( (X*)str,xmle,m)

#define TXB_fromxmldoc(X,Y) TXB_binding( X, TiXmlHandle(Y).FirstChild().ToElement(), 1)
#define TXB_fromxml(X,Y) TXB_binding( X, Y, 1)
#define TXB_toxml(X,Y) TXB_binding( X, Y, 0)
