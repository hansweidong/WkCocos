#include "WkCocosApp/TimerUI.h"

#include "WkCocosApp/GameLogic.h"
#include "WkCocos/Utils/ToolBox.h"

#include "cocos2d.h"
#include "cocos/ui/CocosGUI.h"

USING_NS_CC;

const std::string TimerUI::id = "timer";

TimerUI::TimerUI()
	: Interface()
{
	//filepath is the id for the preload memory ( not used here )
	//m_filepath = id;

	//building UI hierarchy
	m_widget = ui::Layout::create();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	m_startButton = ui::Button::create("SkipNormal.png", "SkipSelected.png");
	m_startButton->addTouchEventListener(CC_CALLBACK_2(TimerUI::startCallback, this));
	m_startButton->setPosition(Vec2(visibleSize.width * 0.25, visibleSize.height * 0.25));
	m_widget->addChild(m_startButton);

	m_startLabel = ui::Text::create("START", "Arial", 21);
	m_startLabel->setPosition(m_startButton->getPosition() + Vec2(0, m_startButton->getContentSize().height));
	m_widget->addChild(m_startLabel);

	m_stopButton = ui::Button::create("SkipNormal.png", "SkipSelected.png");
	m_stopButton->addTouchEventListener(CC_CALLBACK_2(TimerUI::stopCallback, this));
	m_stopButton->setPosition(Vec2(visibleSize.width * 0.75, visibleSize.height * 0.25));
	m_widget->addChild(m_stopButton);

	m_stopLabel = ui::Text::create("STOP", "Arial", 21);
	m_stopLabel->setPosition(m_stopButton->getPosition() + Vec2(0, m_stopButton->getContentSize().height));
	m_widget->addChild(m_stopLabel);
	
	m_countLabel = ui::Text::create("", "Arial", 21);
	m_countLabel->setPosition(Vec2(visibleSize.width * 0.5, visibleSize.height * 0.25));
	m_widget->addChild(m_countLabel);

	if (m_widget)
	{
		m_widget->retain(); //we need to retain it in memory ( or cocos will drop it )
		widget_cache.insert(std::pair<std::string, ui::Widget*>(id, m_widget));
	}

}

TimerUI::~TimerUI()
{}

void TimerUI::startCallback(Ref* widgetRef, ui::Widget::TouchEventType input)
{
	if (input == ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("START BUTTON CLICKED");

		GameLogic::Instance().getPlayer().setTimer("testing", 156, [=](std::string id, unsigned long elapsed){
			m_countLabel->setText(WkCocos::ToolBox::itoa(elapsed));
		});
	}
}


void TimerUI::stopCallback(Ref* widgetRef, ui::Widget::TouchEventType input)
{
	if (input == ui::Widget::TouchEventType::ENDED)
	{
		CCLOG("STOP BUTTON CLICKED");

		GameLogic::Instance().getPlayer().deleteTimer("testing");
	}
}

