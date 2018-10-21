#include "oui/attribute/OUI_Attribute.h"
#include "osal/OSAL_Attribute.h"
#include "util/OUI_StringUtil.h"

#include <iostream>

oui::Attribute::~Attribute() {
	//TODO!!!!!
}

oui::Attribute::Attribute() {

}

oui::Attribute::Attribute(const Attribute& a) {
	type = a.type;
	if (a.type == OSAL::Attribute::INT) {
		intVal = a.intVal;
	} else if (a.type == OSAL::Attribute::STRING) {
		stringVal = a.stringVal;
	} else if (a.type == OSAL::Attribute::BOOL) {
		boolVal = a.boolVal;
	} else if (a.type == OSAL::Attribute::DOUBLE) {
		doubleVal = a.doubleVal;
	}
}

oui::Attribute::Attribute(int value) {
	type = OSAL::Attribute::INT;
	intVal = value;
}

oui::Attribute::Attribute(std::string value) : Attribute(convertUTF8toUTF16(value)) {
}

oui::Attribute::Attribute(const char* value) : Attribute(std::string(value)) {
}

oui::Attribute::Attribute(std::u16string value) {
	type = OSAL::Attribute::STRING;
	stringVal = value;
}

oui::Attribute::Attribute(const char16_t* value) : Attribute(std::u16string(value)) {

}

oui::Attribute::Attribute(bool value) {
	type = OSAL::Attribute::BOOL;
	boolVal = value;
}

oui::Attribute::Attribute(double value) {
	type = OSAL::Attribute::DOUBLE;
	doubleVal = value;
}

bool oui::Attribute::equals(Attribute other) {

	//Return false if types are different
	if (type != other.type) {
		return false;
	}

	//Compare member values
	return intVal == other.intVal && stringVal == other.stringVal
		&& boolVal == other.boolVal && doubleVal == other.doubleVal;
}

oui::Attribute* oui::Attribute::clone() {
	switch (type) {
		case OSAL::Attribute::INT:
			return new Attribute(intVal);
			break;
		case OSAL::Attribute::STRING:
			return new Attribute(stringVal);
			break;
		case OSAL::Attribute::BOOL:
			return new Attribute(boolVal);
			break;
		case OSAL::Attribute::DOUBLE:
			return new Attribute(doubleVal);
			break;
	}

	return NULL;//This should be a breakpoint as it should never happen
}