#ifndef AUDITLOG_H
#define AUDITLOG_H

#include <QString>
#include <QVariantMap>

class AuditLog {
public:
    AuditLog();

    qint64 id() const { return m_id; }
    void setId(qint64 id) { m_id = id; }

    qint64 diamondId() const { return m_diamondId; }
    void setDiamondId(qint64 id) { m_diamondId = id; }

    QString action() const { return m_action; }
    void setAction(const QString &action) { m_action = action; }

    QString fieldName() const { return m_fieldName; }
    void setFieldName(const QString &field) { m_fieldName = field; }

    QString oldValue() const { return m_oldValue; }
    void setOldValue(const QString &val) { m_oldValue = val; }

    QString newValue() const { return m_newValue; }
    void setNewValue(const QString &val) { m_newValue = val; }

    QString timestamp() const { return m_timestamp; }
    void setTimestamp(const QString &ts) { m_timestamp = ts; }

    QVariantMap toVariantMap() const;
    static AuditLog fromVariantMap(const QVariantMap &map);

private:
    qint64 m_id;
    qint64 m_diamondId;
    QString m_action;
    QString m_fieldName;
    QString m_oldValue;
    QString m_newValue;
    QString m_timestamp;
};

#endif
