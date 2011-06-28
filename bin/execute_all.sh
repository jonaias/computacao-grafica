#!/bin/bash
#create dot file

./generate_dot.sh | ./generate_graph.sh

evince hierarchy_model.pdf
