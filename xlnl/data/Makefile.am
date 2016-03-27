#

graph_dir = graph/sample-3.1.7

install-data-local:
	test -d $(HOME)/.lnl || $(mkdir_p) $(HOME)/.lnl
	test -d $(HOME)/.lnl/xlnl || $(mkdir_p) $(HOME)/.lnl/xlnl
	test -d $(HOME)/.lnl/xlnl/graph || $(mkdir_p) $(HOME)/.lnl/xlnl/graph
	cp -prf $(graph_dir) $(HOME)/.lnl/xlnl/graph

uninstall-local:
	rm -rf $(HOME)/.lnl/xlnl

EXTRA_DIST = $(graph_dir)


#graphdir = $(HOME)/.lnl/xlnl
#dist_graph_DATA = graph

#$(HOME)/.lnl/xlnl/graph: graph
#	cp -rf graph $(HOME)/.lnl/xlnl/

#install-data-local:
#	cp -prfP graph/* $(HOME)/.lnl/xlnl

