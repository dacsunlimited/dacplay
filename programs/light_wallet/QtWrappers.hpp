#pragma once

#include <QDateTime>
#include <QLatin1String>
#include <QObject>
#include <QDebug>
#include <QQmlListProperty>

#include <bts/light_wallet/light_wallet.hpp>

#include "QtConversions.hpp"

class LedgerEntry : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString sender MEMBER m_sender NOTIFY stub)
   Q_PROPERTY(QString receiver MEMBER m_receiver NOTIFY stub)
   Q_PROPERTY(qreal amount MEMBER m_amount NOTIFY stub)
   Q_PROPERTY(QString symbol MEMBER m_symbol NOTIFY stub)
   Q_PROPERTY(QString memo MEMBER m_memo NOTIFY stub)

   QString m_sender;
   QString m_receiver;
   qreal m_amount;
   QString m_symbol;
   QString m_memo;

public:
   LedgerEntry(QObject* parent = nullptr): QObject(parent){}
   ~LedgerEntry(){}

Q_SIGNALS:
   //None of the properties change, so squelch warnings by setting this as their NOTIFY property
   void stub();
};

class TransactionSummary : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString id MEMBER m_id NOTIFY stub)
   Q_PROPERTY(QDateTime when MEMBER m_when NOTIFY stub)
   Q_PROPERTY(QQmlListProperty<LedgerEntry> ledger READ ledger CONSTANT)

public:
   TransactionSummary(QString id, QDateTime timestamp, QList<LedgerEntry*>&& ledger, QObject* parent = nullptr);
   ~TransactionSummary(){}

   QQmlListProperty<LedgerEntry> ledger()
   {
      return QQmlListProperty<LedgerEntry>(this, m_ledger);
   }

private:
   QString m_id;
   QDateTime m_when;
   QList<LedgerEntry*> m_ledger;

Q_SIGNALS:
   //None of the properties change, so squelch warnings by setting this as their NOTIFY property
   void stub();
};

class Balance : public QObject
{
   Q_OBJECT
   Q_PROPERTY(QString symbol MEMBER m_symbol NOTIFY symbolChanged)
   Q_PROPERTY(qreal amount MEMBER m_amount NOTIFY amountChanged)

   QString m_symbol;
   qreal m_amount;

public:
   Balance(QString symbol, qreal amount, QObject* parent = nullptr)
      : QObject(parent),
        m_symbol(symbol),
        m_amount(amount)
   {}
   virtual ~Balance(){}
Q_SIGNALS:
   void symbolChanged(qreal arg);
   void amountChanged(qreal arg);
};
