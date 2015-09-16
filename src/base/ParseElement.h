#ifndef __DATA_PARSE_ELEMENT_H__
#define __DATA_PARSE_ELEMENT_H__

#include "ParseAttribute.h"

#include <string>
#include <vector>
#include <iostream>

# define YARS_DATA_PARSE_ELEMENT_TYPE_OPENING 2001
# define YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING 2002

using namespace std;

/**
 * @brief Interface between parser and representation.
 *
 * @sa ParseAttribute
 */
class ParseElement : public std::vector<ParseAttribute*>
{
  public:
    /**
     * @brief Constructor. The type is one of:
     * <ul>
     *   <li> YARS_DATA_PARSE_ELEMENT_TYPE_OPENING </li>
     *   <li> YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING </li>
     * </ul>
     *
     * @param type
     */
    ParseElement(int type);

    /**
     * @brief Destructor.
     */
    ~ParseElement();

    /**
     * @brief Returns the name of the tag.
     *
     * @return name
     */
    string name();

    /**
     * @brief Sets the name, given as char*.
     *
     * @param name
     */
    void setName(char *name);

    /**
     * @brief Sets the name, given as string.
     *
     * @param name
     */
    void setName(string name);

    /**
     * @brief Adds an attribute to this element.
     *
     * @param attribute
     */
    void add(ParseAttribute *attribute);

    /**
     * @brief Returns the attribute, which is identified by its name, on NULL
     * if no attribute with the specified name was found.
     *
     * @param name
     *
     * @return attribute, or NULL if not found
     * @s ParseAttribute
     */
    ParseAttribute* attribute(string name);
    bool hasAttriute(string name);

    /**
     * @brief Returns if this element is an specific opening tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING  && name == name
     *
     * @param name
     *
     * @return true/false
     */
    bool opening(char *name);

    /**
     * @brief Returns if this element is an specific opening tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_OPENING  && name == name
     *
     * @param name
     *
     * @return true/false
     */
    bool opening(string name);


    /**
     * @brief Returns if this element is a specific closing tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING  && name == name
     *
     * @param name
     *
     * @return
     */
    bool closing(char *name);

    /**
     * @brief Returns if this element is a specific closing tag.
     *
     * Returns type == YARS_DATA_PARSE_ELEMENT_TYPE_CLOSING  && name == name
     *
     * @param name
     *
     * @return
     */
    bool closing(string name);

    void set(string name, double &value);
    void set(string name, string &value);
    void set(string name, bool &value);
    void set(string name, int &value);
    void set(string name, unsigned long &value);

    friend std::ostream& operator<<(std::ostream& str, const ParseElement& d)
    {
      str << d._name << ": " << d._type;
      return str;
    };


  private:
    string _name;
    int    _type;
};

#endif // __DATA_PARSE_ELEMENT_H__
