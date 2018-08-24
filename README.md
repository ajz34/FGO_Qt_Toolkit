# FGO Qt Toolkit

This program should be able to let masters make farming plans, or at least list what should farm. 

However, it has not reached author's minimum requirement yet.

## Implementation

* Qt 5.11 (LGPL license) / Visual Studio 2017 (community)
* Windows platform
* For layout consideration, not designed for mobile phone device

## Database and Figure Source

* Servant icon, Exp icon: http://fategrandorder.wikia.com/
	* Lincesed by CC BY-SA 3.0
* Otherwise (including icon, data): https://fate.wiki
	* Licensed by CC BY-NC-SA 4.0

## Code Source

* Qt Example Code (Licensed by BSD)
	* Editable Tree Model Example
		* treeitem.h, treeitem.cpp
		* treemodel.h, treemodel.cpp (modified)
		* xml_editable_mainwindow.h, xml.editable_mainwindow.cpp (modified)
		* xml_editable_mainwindow.ui (modified)
	* Clickable QLabel (https://wiki.qt.io/Clickable_QLabel)
		* qclickablefigurelabel.h, qclickablefigurelabel.cpp (modified)
	* Double Clickable PushButton (http://www.qtcentre.org/threads/44659-Using-double-click-in-QPushButton)
		* idea from https://stackoverflow.com/questions/15658464/qt-rightclick-qpushbutton
		* qdoubleclickpushbutton.cpp, qdoubleclickpushbutton.h

* StackOverflow (Licensed by CC BY-SA 4.0)
	* If stackoverflow source exists, these code may have citation

## License note

<a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/"><img alt="Creative Commons License" style="border-width:0" src="https://i.creativecommons.org/l/by-nc-sa/4.0/88x31.png" /></a><br />This work is licensed under a <a rel="license" href="http://creativecommons.org/licenses/by-nc-sa/4.0/">Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License</a>.

* Aug 24, 2018

The source code and (future) binary will change its license from GPL v3 to CC BY-NC-SA 4.0.
I fond I have included some figures licensed by CC BY-NC-SA 4.0 into the compiled binary, and extracting or replacing these figures is somehow frustrating.
I may change the license if I decided to change the data source from Mooncell wiki to other wiki, or separating data from source code.
