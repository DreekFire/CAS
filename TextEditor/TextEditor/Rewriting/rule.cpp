#include "rule.h"

rule::rule(std::string str_a, std::string str_b) : from(shuntingYardAlg(tokenize(str_a))), replace(shuntingYardAlg(tokenize(str_b))) {

}

rule::rule(node match, node express) : from(match), replace(express) {

}

rule::~rule() {

}

node rule::apply(node express, rule app) {
	node filled(app.from.copy());
	node replacement(app.replace.copy());
	std::vector<node> expressList;
	express.buildList(filled, expressList);
	node::fillProto(filled, expressList);
	if (express.compare(filled)) {
		node::fillProto(replacement, expressList);
		return replacement;
	}
	return express;
}

ruleSet::ruleSet() {

}

ruleSet::ruleSet(std::vector<rule> ruleList) : rules(ruleList) {
	
}

ruleSet::~ruleSet() {

}

void ruleSet::reduce(node& express) {
	node temp = express;
	for (int i = 0; i < (int)rules.size(); i++) {
		temp = express;
		rule::apply(express, rules.at(i));
		if (express.compare(temp)) {
			i = 0;
		}
	}
}

void ruleSet::addRule(rule newRule) {

}