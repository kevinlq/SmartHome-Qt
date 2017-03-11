#include "skinmenu.h"
#include <QDebug>
#include "myhelper.h"

SkinMenu::SkinMenu(QWidget *parent) :
    QMenu(parent)
{
    this->initActions();
    this->initConnect();
}

void SkinMenu::translateActions()
{
    m_action_blue->setText(tr("blue"));
    m_action_navy->setText(tr("navy"));
    m_action_black->setText(tr("black"));
    m_action_gray->setText(tr("gray"));
}

void SkinMenu::setWidgetSkin()
{
    QObject *object = QObject::sender();
    QAction *action = qobject_cast<QAction*>(object);

    myHelper::setStyle(action->objectName());
}

void SkinMenu::initActions()
{
    m_action_blue = new QAction(this);
    m_action_blue->setObjectName(QString("blue"));

    m_action_navy = new QAction(this);
    m_action_navy->setObjectName(QString("navy"));

    m_action_black = new QAction(this);
    m_action_black->setObjectName(QString("black"));

    m_action_gray = new QAction(this);
    m_action_gray->setObjectName(QString("gray"));

    this->addAction(m_action_blue);
    this->addAction(m_action_navy);
    this->addAction(m_action_black);
    this->addAction(m_action_gray);
}

void SkinMenu::initConnect()
{
    connect(m_action_blue,SIGNAL(triggered()),this,SLOT(setWidgetSkin()));
    connect(m_action_navy,SIGNAL(triggered()),this,SLOT(setWidgetSkin()));
    connect(m_action_black,SIGNAL(triggered()),this,SLOT(setWidgetSkin()));
    connect(m_action_gray,SIGNAL(triggered()),this,SLOT(setWidgetSkin()));
}
