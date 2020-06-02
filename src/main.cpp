#include <QCommandLineParser>

#include <src/parser.h>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);
    QCoreApplication::setApplicationName("splispc");
    QCoreApplication::setApplicationVersion("0.0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription(
                "\nsplisp reference compiler\n\n"
                "By Samuel Mahler     <mahlersand@gmail.com>\n"
                "   Jonas Colve       <jonas.colve@outlook.de>\n"
                "   Philipp Rosendahl <philipp.rosendahl@gmx.de>"
    );
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addPositionalArgument("file", "file");

    parser.addOption(QCommandLineOption("kraut", "None needed"));

    parser.process(app);

    //return app.exec();
}
