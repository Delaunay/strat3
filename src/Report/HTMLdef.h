#ifndef STRAT3_REPORT_HTMLDEF_HEADER
#define STRAT3_REPORT_HTMLDEF_HEADER

/*******************************************************************************
 *
 *  Expand html options
 *
 ******************************************************************************/
#define EXPAND_1(a) a
#define EXPAND_2(a, b) a b

#define EXPAND_3(a, ...) EXPAND_2(a, EXPAND_2(__VA_ARGS__))
#define EXPAND_4(a, ...) EXPAND_2(a, EXPAND_3(__VA_ARGS__))
#define EXPAND_5(a, ...) EXPAND_2(a, EXPAND_4(__VA_ARGS__))

#define _NUM_ARGS2(X,X5,X4,X3,X2,X1,N,...) N
#define NUM_ARGS(...) _NUM_ARGS2(0, __VA_ARGS__ ,5,4,3,2,1,0)

#define _EXPAND_3(N, ...) EXPAND_ ## N(__VA_ARGS__)
#define _EXPAND_2(N, ...) _EXPAND_3(N, __VA_ARGS__)
#define EXPAND_N(...)     _EXPAND_2(NUM_ARGS(__VA_ARGS__), __VA_ARGS__)


/*******************************************************************************
 *
 *  HTML Tag Shortcut
 *
 ******************************************************************************/

#define STRINGIFY2( x) #x
#define STRINGIFY(x) STRINGIFY2(x)
#define S(str) STRINGIFY(str)

#define JS_SCRIPT(js)  "<script>" js "</script>"
#define CSS_SCRIPT(css)"<style>" css "</style>"
#define JS_FILE(name)  "<script src=" name "></script>"
#define CSS_FILE(name) "<link rel=\"stylesheet\" href=" name " type=\"text/css\" >"

#define HTML_TAG(tag_beg, tag_end, html, ...) "<" tag_beg EXPAND_N(__VA_ARGS__) ">" #html "</" tag_end ">"

#define HTML_FILE(html)     "<!DOCTYPE html><html>"   html  "</html>"
#define TITLE(title)   "<title>"  title "</title>"

#define H1(name)        "<h1>" name "</h1>"
#define H2(name)        "<h2>" name "</h2>"
#define H3(name)        "<h3>" name "</h3>"
#define H4(name)        "<h4>" name "</h4>"
#define H5(name)        "<h5>" name "</h5>"
#define H6(name)        "<h6>" name "</h6>"

#define HEAD(html)      "<head>"   html "</head>"
#define HEADER(html)    "<header>" html "</header>"
#define FOOTER(html)    "<footer>" html "</footer>"
#define BODY(html)      "<body>"   html "</body>"

#define TABLE(html)     "<table>"  html "</table>"
#define THEAD(html)     "<thead>"  html "</thead>"
#define TBODY(html)     "<tbody>"  html "</tbody>"
#define ROW(html)       "<tr>"     html "</tr>"
#define E(html)         "<td>"     html "</td>"

#define P(html)         "<p>"    html "</p>"
#define SPAN(html)      "<span>" html "</span>"

#define LINK(uri, name) "<a href=" uri  ">" name "</a>"
#define OL(html)        "<ol>"      html "</ol>"
#define LI(name)        "<li>"      name "</li>"

#define LIST_LI(name) LI(LINK("#" name, name))

#define DIV(html, ...)  "<div " EXPAND_N(__VA_ARGS__) ">" html "</div>"

#define CLASS(opt) S(class=)#opt 
#define ID(opt)    S(id=)#opt
#define STYLE(opt) S(style=)#opt

#endif
