#ifndef PRINTSERVICE_H
#define PRINTSERVICE_H

#include <QString>

class PrintService {
public:
    static PrintService &instance();

    bool printDiamondSpecSheet(qint64 diamondId, const QString &outputPath, QString *errorMessage = nullptr);

private:
    PrintService() = default;
    ~PrintService() = default;
    PrintService(const PrintService &) = delete;
    PrintService &operator=(const PrintService &) = delete;
};

#endif
