/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_NODE_HPP_
#define ODS_NODE_HPP_

#include "err.hpp"
#include "global.hxx"
#include "node.hxx"

namespace ods	{ // ods::
class Tag;

class ODS_API Node
{
public:
	Node(const QString&);
	Node(ods::Tag*);
	virtual ~Node();
	
	QString*
	String() { return (QString*) data_; }
	
	ods::Tag*
	Tag() { return (ods::Tag*) data_; }
	
	bool
	IsString() const { return type_ == ods::node::Type::String; }
	
	bool
	IsTag() const { return type_ == ods::node::Type::Tag; }
	
private:
	NO_ASSIGN_COPY_MOVE(Node);
	
	void			*data_ = nullptr;
	ods::node::Type	type_ = ods::node::Type::Tag;
};

} // ods::

#endif
