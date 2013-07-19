#ifndef SVG_C_DEFINITION_H
#define SVG_C_DEFINITION_H

#include <string>
#include <vector>

namespace svg_de
{
	using namespace std;
	
	typedef string length;

	class parsed_length
	{
	public:
		double number;
		string unit; // "em" | "ex" | "px" | "in" | "cm" | "mm" | "pt" | "pc" | "%"
		parsed_length( length content);
	};

	struct animate;
	struct animateColor;
	struct animateMotion;
	struct animateTransform;
	struct set;
	struct desc;
	struct metadata;
	struct title;
	struct circle;
	struct ellipse;
	struct line;
	struct path;
	struct polygon;
	struct polyline;
	struct rect;
	struct defs;
	struct g;
	struct svg;
	struct symbol;
	struct use;
	struct linearGradient;
	struct radialGradient;
	struct a;
	struct altGlyphDef;
	struct clipPath;
	struct color_profile;
	struct cursor;
	struct filter;
	struct font;
	struct font_face;
	struct foreignObject;
	struct image;
	struct marker;
	struct mask;
	struct pattern;
	struct script;
	struct style;
	struct switch_;
	struct text;
	struct view;

	struct animation_elements
	{
		vector<animate>			ANI;
		//vector<animateColor>		ANI_COL;
		//vector<animateMotion>		ANI_MOT;
		//vector<animateTransform>	ANI_TRAN;
		//vector<set>			SET;
	};
	struct descriptive_elements
	{
		vector<desc>			DES;
		vector<metadata>		META;
		vector<title>			TITLE;
	};
	struct shape_elements
	{
		vector<circle>			CIR;
		vector<ellipse>			ELL;
		vector<line>			LN;
		vector<path>			PATH;
		vector<polygon>			POLY_GON;
		vector<polyline>		POLY_LINE;
		vector<rect>			RECT;
	};
	struct structural_elements
	{
		vector<defs>			DEF;
		vector<g>			G;
		//vector<svg>			SVG;
		//it is not a good idea to allow struct SVG to contain a SVG array
		vector<symbol>			SYM;
		vector<use>			USE;
	};
	struct gradient_elements
	{
		vector<linearGradient>		LIN_GRD;
		vector<radialGradient>		RAD_GRD;
	};
	struct etc_elements
	{//18 in total
		//vector<a>			A;
		//vector<altGlyphDef>		ALT_GLY_DEF;
		//vector<clipPath>		CLP_PATH;
		//vector<color_profile>		COL_PRO;
		//vector<cursor>			CUR;
		//vector<filter>			FILTER;
		//vector<font>			FONT;
		//vector<font_face>		FONT_FC;
		//vector<foreignObject>		FOR_OBJ;
		//vector<image>			IMG;
		//vector<marker>			MARKER;
		//vector<mask>			MASK;
		vector<pattern>			PATT;
		//vector<script>			SCRIPT;
		//vector<style>			STYLE;
		//vector<switch_>			SWITCH;
		vector<text>			TXT;
		//vector<view>			VIEW;
	};
	struct conditional_processing_attributes
	{ 
		string requiredFeatures;
		string requiredExtensions;
		string systemLanguage;
	};
	struct core_attributes
	{
		string id;
		string xml_base;  //xml:base
		string xml_lang;  //xml:lang
		string xml_space; //xml:space
	};
	struct document_event_attributes
	{
		string onunload;
		string onabort;
		string onerror;
		string onresize;
		string onscroll;
		string onzoom;
	};
	struct graphical_event_attributes
	{
		string onfocusin;
		string onfocusout;
		string onactivate;
		string onclick;
		string onmousedown;
		string onmouseup;
		string onmouseover;
		string onmousemove;
		string onmouseout;
		string onload;
	};
	struct presentation_attributes
	{
		string alignment_baseline; 
		string baseline_shift; 
		string clip; 
		string clip_path; 
		string clip_rule;
		string color;
		string color_interpolation; 
		string color_interpolation_filters; 
		string color_profile; 
		string color_rendering; 
		string cursor; 
		string direction; 
		string display; 
		string dominant_baseline; 
		string enable_background;
		string fill; 
		string fill_opacity;
		string fill_rule; 
		string filter; 
		string flood_color; 
		string flood_opacity; 
		string font_family; 
		string font_size; 
		string font_size_adjust; 
		string font_stretch; 
		string font_style; 
		string font_variant; 
		string font_weight; 
		string glyph_orientation_horizontal; 
		string glyph_orientation_vertical; 
		string image_rendering; 
		string kerning; 
		string letter_spacing; 
		string lighting_color; 
		string marker_end; 
		string marker_mid; 
		string marker_start; 
		string mask;
		string opacity;
		string overflow; 
		string pointer_events; 
		string shape_rendering; 
		string stop_color; 
		string stop_opacity;
		string stroke;
		string stroke_dasharray; 
		string stroke_dashoffset; 
		string stroke_linecap; 
		string stroke_linejoin; 
		string stroke_miterlimit;
		string stroke_opacity; 
		string stroke_width;
		string text_anchor; 
		string text_decoration; 
		string text_rendering; 
		string unicode_bidi; 
		string visibility; 
		string word_spacing; 
		string writing_mode;
		//in some of the above attributes '-' are replaced by '_'
	};
	struct xlink_attributes
	{
		//in the below 7 attributes, ':' are replaced by '_'
		string xlink_href;
		string xlink_show;
		string xlink_actuate;
		string xlink_type;
		string xlink_role;
		string xlink_arcrole;
		string xlink_title;
	};
	struct common_attributes
	{
		string class_;
		string style;
		string externalResourcesRequired;
	};
	struct common_physical_attributes
	{
		length x;
		length y;
		length width;
		length height;
	};
	struct special_physical_attributes
	{
		string viewBox;
		string preserveAspectRatio;
		string zoomAndPan;
		string baseProfile;
		string contentScriptType;
		string contentStyleType;
		string version;
	};
	struct transform_attribute
	{
			string transform;
	};

	struct svg :	//content elements
			animation_elements,
			descriptive_elements,
			structural_elements,
			shape_elements,
			gradient_elements,
			etc_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			document_event_attributes,
			graphical_event_attributes,
			presentation_attributes,
			common_attributes,
			common_physical_attributes,
			special_physical_attributes
	{
	};
	
	struct g : //content elements
			animation_elements,
			descriptive_elements,
			structural_elements,
			shape_elements,
			gradient_elements,
			etc_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			common_attributes,
			transform_attribute
	{
	};
	
	struct defs : g
	{
	};
	
	struct symbol : //content elements
			animation_elements,
			descriptive_elements,
			shape_elements,
			structural_elements,
			gradient_elements,
			etc_elements,
			//attributes
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			common_attributes
	{
			string preserveAspectRatio;
			string viewBox;
	};
	
	struct use : //content elements
			animation_elements,
			descriptive_elements,
			//attributes
			core_attributes,
			conditional_processing_attributes,
			graphical_event_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes,
			common_physical_attributes,
			transform_attribute
	{
	};
	
	struct animate : //content elements
			descriptive_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			xlink_attributes
	{
	//animation event attributes
		string onbegin;
		string onend;
		string onrepeat;
		string onload;
	//animation attribute target attributes
		string attributeType;
		string attributeName;
	//animation timing attributes
		string begin;
		string dur;
		string end;
		string min;
		string max;
		string restart;
		string repeatCount;
		string repeatDur;
		string fill;
	//animation value attributes
		string calcMode;
		string values;
		string keyTimes;
		string keySplines;
		string from;
		string to;
		string by;
	//animation addition attributes
		string additive;
		string accumulate;
		string externalResourcesRequired;
	};
	
	struct desc : //attributes
		core_attributes
	{
		//content elements: Any elements or character data.
		string class_;
		string style;
	};
	struct title : desc
	{
	};
	struct metadata : //attributes
		core_attributes
	{
	};
	
	struct shapes : //content elements
		animation_elements,
		descriptive_elements,
		//attributes
		conditional_processing_attributes,
		core_attributes,
		graphical_event_attributes,
		presentation_attributes,
		common_attributes,
		transform_attribute
	{
	};
	
	struct rect : shapes,
			common_physical_attributes
	{
		length rx;
		length ry;
	};
	
	struct circle : shapes
	{
		length cx;
		length cy;
		length r;
	};
	
	struct ellipse : shapes
	{
		length cx;
		length cy;
		length rx;
		length ry;
	};
	
	struct line : shapes
	{
		length x1;
		length y1;
		length x2;
		length y2;
	};
	
	struct polyline : shapes
	{
		string points;
	};
	
	struct polygon : polyline
	{
	};
	
	struct stop;
	struct gradient : //content elements
			descriptive_elements,
			//attributes
			core_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes
	{
		vector<animate>			ANI;
		//vector<animateTransform>	ANI_TRAN;
		vector<set>			SET;
		vector<stop>			STOP;
		string gradientUnits;
		string gradientTransform;
		string spreadMethod;
	};
	
	struct linearGradient : gradient
	{
		length x1;
		length y1;
		length x2;
		length y2;
	};
	struct radialGradient : gradient
	{
		length cx;
		length cy;
		length r;
		length fx;
		length fy;
	};
	
	struct pattern : //content elements
			animation_elements,
			descriptive_elements,
			shape_elements,
			structural_elements,
			gradient_elements,
			etc_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes,
			common_physical_attributes
	{
		string viewBox;
		string preserveAspectRatio;
		string patternUnits;
		string patternContentUnits;
		string patternTransform;
	};
	
	struct tref : //content elements
			descriptive_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes
	{
		vector<animate>			ANI;
		//vector<animateColor>		ANI_COL;
		//vector<set>			SET;
	};
	struct tspan;
	struct altGlyph;
	struct text_content_child_elements
	{
		//vector<a>			A;
		//vector<altGlyph>			ALT_GLY
		vector<tref>					TREF;
		vector<tspan>				TSPAN;
	};
	struct text_shared_attributes
	{
		string lengthAdjust;
		length x;
		length y;
		length dx;
		length dy;
		length rotate;
		string textLength;
	};
	struct tspan : //content elements
			descriptive_elements,
			text_content_child_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			common_attributes,
			text_shared_attributes
	{
		vector<animate>			ANI;
		//vector<animateColor>		ANI_COL;
		//vector<set>			SET;
	};
	struct textPath : //content elements
			descriptive_elements,
			text_content_child_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes
	{
		vector<animate>			ANI;
		//vector<animateColor>		ANI_COL;
		//vector<set>			SET;
		string startOffset;
		string method;
		string spacing;
	};
	struct altGlyph : //attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			xlink_attributes,
			common_attributes
	{
		//content elements: Any elements or character data.
		length x;
		length y;
		length dx;
		length dy;
		string glyphRef;
		string format;
		string rotate;
	};
	struct text : //content elements
			animation_elements,
			descriptive_elements,
			text_content_child_elements,
			//attributes
			conditional_processing_attributes,
			core_attributes,
			graphical_event_attributes,
			presentation_attributes,
			common_attributes,
			transform_attribute,
			text_shared_attributes
	{
		//vector<textPath>			TXT_PT;
	};

};//end of namespace svg_de

#endif
