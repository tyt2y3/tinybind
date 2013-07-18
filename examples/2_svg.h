STRUCT(path)
{
	ATTR(string, d);
	ATTR(string, stroke);
	ATTR_NAME(double, strokeWidth, "stroke-width");
	ATTR(string, fill);
};

STRUCT(stop)
{
	ATTR(double, offset);
	ATTR_NAME(string, stopColor, "stop-color");
	ATTR_NAME(string, stopOpacity, "stop-opacity");
};

STRUCT(baseobject)
{
	ATTR(string, id);
	ATTR(int, width);
	ATTR(int, height);

	#ifdef TXB_FIRST_PASS
public:
	baseobject()
	{
		width=0; height=0;
	}
	#endif
};

STRUCT_INHERIT(linearGradient, baseobject)
{
	CHILD(stop, stops);
	INHERIT(baseobject);
};

STRUCT(defs)
{
	CHILD(linearGradient, linearGradients);
};

STRUCT_INHERIT(svg, baseobject)
{
	ATTR(string, version);
	ATTR(string, baseProfile);
	ATTR(string, xmlns);
	CHILD(defs, defss);
	CHILD(path, paths);
	INHERIT(baseobject);
	
	ATTR_PRIVATE(string,private_string);
};
