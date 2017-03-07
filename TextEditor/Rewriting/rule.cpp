#include "rule.h"

rule::rule(std::string str_a, std::string str_b) : from(shuntingYardAlg(tokenize(str_a))), replace(shuntingYardAlg(tokenize(str_b))) {

}

rule::rule(tree match, tree express) : from(match), replace(express) {

}

rule::~rule() {

}

node rule::apply(tree express) {
	node filled(from.root.copy());
	node replacement(replace.root.copy());
	std::vector<node> expressList;
	express.root.buildList(filled, expressList);
	node::fillProto(filled, expressList);
	if (express.root.compare(filled)) {
		node::fillProto(replacement, expressList);
		return replacement;
	}
	return express.root;
}

ruleSet::ruleSet() {

}

ruleSet::ruleSet(std::vector<rule> ruleList) : rules(ruleList) {
	
}

ruleSet::~ruleSet() {

}

void ruleSet::reduce(tree& express) {
	tree temp = express;
	for (int i = 0; i < rules.size(); i++) {
		temp = express;
		rules.at(i).apply(express);
		if (express.root.compare(temp.root)) {
			i = 0;
		}
	}
}

void ruleSet::addRule(rule newRule) {

}