# Copyright © 2007-2017 Jakub Wilk <jwilk@jwilk.net>
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the “Software”), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED “AS IS”, WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

xml_files = $(wildcard *.xml)
man_files = $(xml_files:.xml=.8)

docbook_xsl = http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl
xsltproc_opts = --nonet --param man.authors.section.enabled 0

.PHONY: all
all: $(man_files)
	echo $(man_files)

%.8: %.xml
	xsltproc $(xsltproc_opts) $(docbook_xsl) $(<)

.PHONY: clean
clean:
	rm -f *.8

# vim:ts=4 sts=4 sw=4 noet
