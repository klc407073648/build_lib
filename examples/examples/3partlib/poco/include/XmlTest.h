#include <string>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <Poco/AutoPtr.h>                   //Poco::AutoPtr
#include <Poco/DOM/Document.h>              // Poco::XML::Document
#include <Poco/DOM/Element.h>               // Poco::XML::Element
#include <Poco/DOM/Text.h>                  // Poco::XML::Text
#include <Poco/DOM/CDATASection.h>          // Poco::XML::CDATASection
#include <Poco/DOM/ProcessingInstruction.h> // Poco::XML::ProcessingInstruction
#include <Poco/DOM/Comment.h>               // Poco::XML::Comment
#include <Poco/DOM/DOMWriter.h>             // Poco::XML::DOMWriter
#include <Poco/XML/XMLWriter.h>             // Poco::XML::XMLWriter
#include <Poco/DOM/DOMParser.h>
#include <Poco/DOM/Document.h>
#include <Poco/DOM/Node.h>
#include <Poco/DOM/NamedNodeMap.h>
#include <Poco/XML/XMLString.h>
#include <Poco/XML/XMLException.h>
#include <Poco/XML/XMLStream.h>
#include <Poco/DOM/NodeIterator.h>
#include <Poco/DOM/NodeFilter.h>

void read_xml()
{

    Poco::XML::DOMParser parser;

    Poco::AutoPtr<Poco::XML::Document> doc = parser.parse("./example.xml");
    Poco::XML::NodeIterator it(doc, Poco::XML::NodeFilter::SHOW_ALL); // SHOW_ELEMENT SHOW_ATTRIBUTE  SHOW_TEXT  SHOW_CDATA_SECTION
    Poco::XML::Node *node = it.nextNode();

    int i = 0;
    while (node)
    {
        if (node->nodeType() != Poco::XML::Node::ELEMENT_NODE) // code example
        {
            node = it.nextNode();
            continue;
        }
        if (node->nodeName() == "#text") // code example
        {
            node = it.nextNode();
            continue;
        }
        if (node->nodeName() == "#cdata-section") // code example
        {
            node = it.nextNode();
            continue;
        }

        std::cout << "node:" << i << ":" << node->nodeName() << ":" << node->nodeValue() << std::endl;
        Poco::XML::NamedNodeMap *map = node->attributes();
        if (map)
        {
            for (size_t i = 0; i < map->length(); ++i)
            {
                Poco::XML::Node *c = map->item(i);
                std::string n1 = c->nodeName();
                std::string v1 = c->nodeValue();

                std::cout << "map:" << n1 << ":" << v1 << std::endl;
            }
        }
        node = it.nextNode();
    }
}

void write_xml()
{
    Poco::AutoPtr<Poco::XML::Document> doc = new Poco::XML::Document;
    // custom declaration
    Poco::AutoPtr<Poco::XML::ProcessingInstruction> pi = doc->createProcessingInstruction("xml", "version='1.0' encoding='UTF-8'");
    Poco::AutoPtr<Poco::XML::Comment> comment = doc->createComment("This is comment.");
    Poco::AutoPtr<Poco::XML::Element> e_root = doc->createElement("root_element");

    Poco::AutoPtr<Poco::XML::Element> e_child_a = doc->createElement("child_element_a");
    e_child_a->setAttribute("a1", "1");
    e_child_a->setAttribute("a2", "2");

    Poco::AutoPtr<Poco::XML::Element> e_child_b = doc->createElement("child_element_b");
    e_child_b->setAttribute("b1", "3");
    e_child_b->setAttribute("b2", "4");

    Poco::AutoPtr<Poco::XML::Text> txt = doc->createTextNode("txt_content");
    Poco::AutoPtr<Poco::XML::CDATASection> cdata = doc->createCDATASection("ignore parse txt !@#$%^&*()");

    doc->appendChild(pi);
    doc->appendChild(comment);
    doc->appendChild(e_root);
    e_root->appendChild(e_child_a);
    e_root->appendChild(e_child_b);

    e_root->appendChild(cdata);
    e_root->appendChild(txt);

    Poco::XML::DOMWriter writer;

    // writer.setOptions(Poco::XML::XMLWriter::CANONICAL);
    // writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT_ATTRIBUTES); //
    // writer.setOptions(Poco::XML::XMLWriter::CANONICAL_XML);
    // writer.setOptions(Poco::XML::XMLWriter::WRITE_XML_DECLARATION);// add <?xml version='1.0' encoding='UTF-8'?>
    writer.setOptions(Poco::XML::XMLWriter::PRETTY_PRINT);

    writer.writeNode("./example.xml", doc);
    // string test
    std::stringstream sstr;
    writer.writeNode(sstr, doc);
    std::string s = sstr.str();
    std::cout << s << std::endl;
}

void XmlTest()
{
    write_xml();
    // read_xml();
}
