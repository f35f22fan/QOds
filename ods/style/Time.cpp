#include "Time.hpp"

#include "../Book.hpp"
#include "../TimeInfo.hpp"
#include "../Ns.hpp"
#include "Manager.hpp"
#include "style.hxx"
#include "tag.hh"
#include "../Tag.hpp"

namespace ods	{ // ods::
namespace style	{ // ods::style::

Time::Time(ods::Book *book,
	const ods::StylePlace place) :
	book_(book),
	place_(place)
{
	auto &ns = (place == ods::StylePlace::ContentFile) ?
		book_->content()->ns() : book_->style_manager()->ns();
	tag_ = ods::style::tag::NumberTimeStyle(ns, nullptr);
	Init();
}

Time::~Time()
{
	if (info_ != nullptr)
		delete info_;
}

void
Time::AddHours()
{
	auto *day_tag = GetTag(ods::style::tag::NumberHours);
	day_tag->AttrSet(tag_->ns().number(), ods::ns::kStyle,
		info_->hours_number_style());
}

void
Time::AddMinutes()
{
	auto *day_tag = GetTag(ods::style::tag::NumberMinutes);
	day_tag->AttrSet(tag_->ns().number(), ods::ns::kStyle,
		info_->minutes_number_style());
}

void
Time::AddSeconds()
{
	auto *day_tag = GetTag(ods::style::tag::NumberSeconds);
	day_tag->AttrSet(tag_->ns().number(), ods::ns::kStyle,
		info_->seconds_number_style());
}

void
Time::AddSeparator(const qint8 id)
{
	auto *sep_tag1 = GetTag(ods::tag::NumberText, id);
	const QString separator = info_->SeparatorAsString();
	sep_tag1->SubnodeAdd(new ods::Node(separator));
}

ods::Tag*
Time::GetTag(ods::tag::func f, const qint8 id_num)
{
	auto *tag = tag_->GetSubtag(f, id_num);
	if (tag != nullptr)
		return tag;
	tag = f(tag_->ns(), nullptr);
	tag->id_num_set(id_num);
	tag_->SubtagAdd(tag);
	return tag;
}

void
Time::Init()
{
	SetUniqueName();
}


void
Time::SetInfo(const ods::TimeInfo &info)
{
	if (info_ == nullptr)
		info_ = new ods::TimeInfo();
	info_->CopyFrom(info);

	/**
	<number:time-style style:name="N40">
	  <number:hours number:style="long"/>
	  <number:text>:</number:text>
	  <number:minutes number:style="long"/>
	</number:time-style>
	**/

	/**
	enum class Order : quint8 {
		HOURS_MINUTES,
		HOURS_MINUTES_SECONDS
	};
	**/
	const auto order = info_->order();
	if (order == ods::timeinfo::Order::HOURS_MINUTES)
	{
		AddHours();
		AddSeparator(0);
		AddMinutes();
	} else if (order == ods::timeinfo::Order::HOURS_MINUTES_SECONDS) {
		AddHours();
		AddSeparator(0);
		AddMinutes();
		AddSeparator(1);
		AddSeconds();
	}
}

void
Time::SetUniqueName()
{
	const QString base = (place_ == ods::StylePlace::StylesFile) ?
		QLatin1String("time_st") : QLatin1String("time_cn");

	int i = 0;
	while (true)
	{
		name_ = base + QString::number(i++);
		if (book_->GetTimeStyle(name_) == nullptr)
			break;
	}
	tag_->AttrSet(tag_->ns().style(), ods::ns::kName, name_);
}

} // ods::style::
} // ods::
