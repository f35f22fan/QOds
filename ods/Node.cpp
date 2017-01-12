/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#include "Node.hpp"
#include "Tag.hpp"

namespace ods	{ // ods::

Node::Node(const QString &s)
{
	data_ = new QString(s);
	type_ = ods::node::Type::String;
}

Node::Node(ods::Tag *tag)
{
	data_ = tag;
}

Node::~Node()
{
	if (IsTag())
		delete Tag();
	else if (IsString())
		delete String();
	else
		mtl_line("fixme");
}

} // ods::
