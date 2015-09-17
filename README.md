# MyWebBank
A simulation of web banks. C++ Assignment.

 - 2015-8-27 **Program started.** Start designing overall structure and UI frames.
 - 2015-8-28 **Logic part:** WClasses declared, WUser realized. **UI part:** tried basic QSS format, viewed Material Design Guide, main window structure decided. Special help from An Liang for the logic-UI interface.
 - 2015-8-31 **Logic part:** WDBManip done and partly debugged, WebBankCurrentUser added for the convenience of further use. **UI part:** change in layout including detailed subjects in left nav bar and remove of "current dir" bar, add dynamic translation and two main interfaces, style of QLabel, QLineEdit, QComboBox and QPushButtl established. 
 - 2015-9-1 **Logic part:** WAccont start, basic functions like interest calculation done, WTransfer half done. **UI part:** Motion Design on opening and closing the main window done, tried QMovie with gif, but finally go with QPropertyAnimator, the curve presets work fine.
 - 2015-9-3 **Logic part:** WUser, WCurrentUser, WDBManip done, WAccount done but still needs inherit and part with WPayment still undone, start WPayment, WCreditCard, WMessage tomorrow. **UI part:** encapsuled top and left bars into two widgets and added animation, style of QTableWidget, QCheckBox established, add Login and Register window and corresponding animations, centerStack pages half done.
 - 2015-9-4 **Logic part:** WUser, WCurrentUser, WDBManip, WTransfer done, 70% of WAccount done. **UI part:** add Login/Register window, table QSS done, first six stackedwidgets done.
 - 2015-9-6 **Logic part:** WDBManip tested and debugged, revise some of its functions, WPayment finished, test project established. **UI part:** loading window added, translation record file written, animation effect polished.
 - 2015-9-7 **Logic part:** WPayment, WAccount, WMessage finished, WQuery ongoing and to be finished tomorrow. **UI part:** welcome page created, calendar widget style set, translation updated, comments added.
 - 2015-9-8 **Logic part:** all classes except WCreditCard done, comments added. **UI part:** static release version tested, program icon/logo added.
 - 2015-9-9 Rest for 4 days. Group Members prepare for tests and cadre training.
 - 2015-9-13 Continue working. **Logic part:** tests conducted on almost all classes and the result turned out well, minor functions revised. **UI part:** translation polished, translator initiation process corrected, unrelated images deleted.
 - 2015-9-14 **Union of Logic and UI start.** Start combining database. **Union:** login process, account page, account query page, transfer page, current fix exchange page and payment page union done. Change database open method to global variable for the UI classes. Logout loop added.
 - 2015-9-15 **Union:** payment page, user info page, change password page, system information page done. Only credit card pages and autopay page left to union.
 - 2015-9-16 **Union:** minor bugs still exists and need further debugging. Minor bugs tested and fixed. Fault-tolerant mechanism and multiple color themes added. Change to float display in tables. Instant table update added.
 - 2015-9-17 **Union:** Officially finished. Log info table added and tested, more credit card type available, transaction records export as xls now supported.