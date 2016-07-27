#!/bin/bash
if [ '$#' -eq 1 ]
then
	echo Do stuff...
else
	echo Not enough arguments
	echo Usage: script ARGS
fi
