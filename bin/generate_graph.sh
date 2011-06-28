#!/bin/bash
#create graph

dot -Tps2 | ps2pdf - hierarchy_model.pdf
