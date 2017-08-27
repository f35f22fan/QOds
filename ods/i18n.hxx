/*
 * Copyright © 2014 f35f22fan@gmail.com
 *
 * Read the LICENSE file that comes with this project for license details.
*/

#ifndef ODS_I18N_HXX_
#define ODS_I18N_HXX_

#include <QtGlobal>
#include <QString>

namespace ods	{ // ods::
namespace i18n	{ // ods::i18n::

enum class Id : quint16 {
	NotSet = 0,
	Brazil,
	Canada,
	China,
	France,
	Germany,
	India,
	Italy,
	Luxembourg,
	Pakistan,
	Russia,
	Spain,
	Sweden,
	Turkey,
	UK,
	USA
};

struct Country {
	ods::i18n::Id id;
	QString str;
};

const Country kBrazil { ods::i18n::Id::Brazil, QLatin1String("BR") };
const Country kCanada { ods::i18n::Id::Canada, QLatin1String("CA") };
const Country kChina { ods::i18n::Id::China, QLatin1String("CN") };
const Country kFrance { ods::i18n::Id::France, QLatin1String("FR") };
const Country kGermany { ods::i18n::Id::Germany, QLatin1String("DE") };
const Country kIndia { ods::i18n::Id::India, QLatin1String("IN") };
const Country kItaly { ods::i18n::Id::Italy, QLatin1String("IT") };
const Country kLuxembourg { ods::i18n::Id::Luxembourg, QLatin1String("LU") };
const Country kPakistan { ods::i18n::Id::Pakistan, QLatin1String("PK") };
const Country kRussia { ods::i18n::Id::Russia, QLatin1String("RU") };
const Country kSpain { ods::i18n::Id::Spain, QLatin1String("ES") };
const Country kSweden { ods::i18n::Id::Sweden, QLatin1String("SE") };
const Country kTurkey { ods::i18n::Id::Turkey, QLatin1String("TR") };
const Country kUK { ods::i18n::Id::UK, QLatin1String("GB") };
const Country kUSA { ods::i18n::Id::USA, QLatin1String("US") };

enum class CurrencyId : quint16 {
	USD,
	EUR,
	GbPound, // British pound
	Renminbi, // Chinese
	RusRuble // Russian
};

struct Currency {
	CurrencyId id;
	QString sign;
	QString iso;
};

const Currency kUSD = { CurrencyId::USD, QLatin1String("$"), QLatin1String("USD") };
const Currency kEuro = { CurrencyId::EUR, QLatin1String("€"), QLatin1String("EUR") };
const Currency kGbPound = { CurrencyId::GbPound, QLatin1String("₤"), QLatin1String("GBP") };
const Currency kRenminbi = { CurrencyId::Renminbi, QLatin1String("¥"), QLatin1String("CNY") };
const Currency kRusRuble = { CurrencyId::RusRuble, QLatin1String("₽"), QLatin1String("RUB") };

enum class LanguageId : quint16 {
	NotSet = 0,
	Arabic,
	Chinese,
	English,
	French,
	German,
	Italian,
	Portuguese,
	Russian,
	Spanish,
	Turkish
};

struct Language {
	ods::i18n::LanguageId	id;
	QString str;
};

const Language kArabic { LanguageId::Arabic, QLatin1String("ar") };
const Language kChinese { LanguageId::Chinese, QLatin1String("zh") };
const Language kEnglish { LanguageId::English, QLatin1String("en") };
const Language kFrench { LanguageId::French, QLatin1String("fr") };
const Language kGerman { LanguageId::German, QLatin1String("de") };
const Language kItalian { LanguageId::Italian, QLatin1String("it") };
const Language kPortuguese { LanguageId::Portuguese, QLatin1String("pt") };
const Language kRussian { LanguageId::Russian, QLatin1String("ru") };
const Language kSpanish { LanguageId::Spanish, QLatin1String("es") };
const Language kTurkish { LanguageId::Turkish, QLatin1String("tr") };

} // ods::i18n::
} // ods::

#endif
