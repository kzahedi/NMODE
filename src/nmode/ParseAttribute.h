#ifndef __DATA_PARSE_ATTRIBUTE_H__
#define __DATA_PARSE_ATTRIBUTE_H__

#include <string>

using namespace std;

/**
 * @brief Container for the attributes of an xml element
 * @sa DataParseElement
 */
class ParseAttribute
{
  public:
    /**
     * @brief Constructor
     */
    ParseAttribute();

    /**
     * @brief Destructor (Does nothing)
     */
    ~ParseAttribute();

    /**
     * @brief Set the name of the attribute.
     *
     * @param name
     */
    void setName(string name);

    /**
     * @brief Set the value of the attribute. The value is naturally given as
     * string, because it is retrieved from an XML file.
     *
     * @param value
     */
    void setValue(string value);

    /**
     * @brief Returns the name of the attribute.
     *
     * @return name
     */
    string name();

    /**
     * @brief Returns the string-value of the value.
     *
     * @return value (string)
     */
    string value();

    /**
     * @brief Returns the value converted by atoi. ParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (int)
     */
    int intValue();

    /**
     * @brief Returns the value converted from atoi to unsigned long.
     * ParseAttribute cannot know of which type the value is. Therefore,
     * there is no error handling.
     *
     * @return value (int)
     */
    unsigned long unsignedlongValue();

    /**
     * @brief Returns if value is equal to "true". ParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (bool)
     */
    bool boolValue();

    /**
     * @brief Returns the value converted by atof. ParseAttribute cannot know
     * of which type the value is. Therefore, there is no error handling.
     *
     * @return value (double)
     */
    double realValue();

  private:
    string _name;
    string _value;
};

#endif // __DATA_PARSE_ATTRIBUTE_H__
