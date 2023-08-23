# Yandex Easy Monetization SDK for Defold
_“This plugin is not endorsed or sponsored by Yandex LLC. This is an independent, unofficial plugin. “_

Defold [native extension](https://www.defold.com/manuals/extensions/) which provides access to Yandex Mobile Ads SDK functionality on Android(only).

# Setup

## How do I use this extension?

You can use the Yandex Mobile Ads SDK for Defold extension in your own project by adding this project as a [Defold library dependency](http://www.defold.com/manuals/libraries/).
Open your game.project file and in the dependencies field under project add:

>https://github.com/osov/defold-yandex-easy-monetization/archive/main.zip
or point to the ZIP file of a [specific release](https://github.com/osov/defold-yandex-easy-monetization/releases).

Please, read [Android API docs](https://yandex.ru/dev/mobile-ads/doc/android/quick-start/)

# Lua API

## Methods

	yandexads.set_callback(listener)
	yandexads.initialize()

	yandexads.load_banner(adUnit)
	yandexads.is_banner_loaded()
	yandexads.show_banner()
	yandexads.hide_banner()
	yandexads.destroy_banner()

	yandexads.load_interstitial(adUnit)
	yandexads.is_interstitial_loaded()
	yandexads.show_interstitial()

	yandexads.load_rewarded(adUnit)
	yandexads.is_rewarded_loaded()
	yandexads.show_rewarded()
	yandexads.set_user_consent(boolean)


## Constants

	yandexads.MSG_ADS_INITED
	yandexads.MSG_INTERSTITIAL
	yandexads.MSG_REWARDED
	yandexads.MSG_BANNER

	yandexads.EVENT_LOADED
	yandexads.EVENT_ERROR_LOAD
	yandexads.EVENT_SHOWN
	yandexads.EVENT_DISMISSED
	yandexads.EVENT_CLICKED
	yandexads.EVENT_IMPRESSION
	yandexads.EVENT_NOT_LOADED
	yandexads.EVENT_REWARDED
	yandexads.EVENT_DESTROYED
	
	yandexads.POS_NONE
	yandexads.POS_TOP_LEFT
	yandexads.POS_TOP_CENTER
	yandexads.POS_TOP_RIGHT
	yandexads.POS_BOTTOM_LEFT
	yandexads.POS_BOTTOM_CENTER
	yandexads.POS_BOTTOM_RIGHT
	yandexads.POS_CENTER

# How to use ?

1) set up an event handling callback
2) run initialization
3) load desired ad format
```lua
local function listener(self, message_id, message)
    if message_id == yandexads.MSG_ADS_INITED then
    -- extension is ready to load ads
    end
end

yandexads.set_callback(listener) -- (1)
yandexads.initialize() -- (2)
```


## BANNER

```lua
local function listener(self, message_id, message)
    if message_id == yandexads.MSG_ADS_INITED then
       yandexads.load_banner('R-M-DEMO-300x250')
    end

    if message_id == yandexads.MSG_BANNER then
       if event == yandexads.EVENT_LOADED then
          yandexads.show_banner(yandexads.BOTTOM_CENTER) -- optional position(default BOTTOM_CENTER)
       end
    end
end
```

Fixed parameters are set:
   size - AdSize.flexibleSize(320,50)


## INTERSTITIAL

```lua
local function listener(self, message_id, message)
    if message_id == yandexads.MSG_ADS_INITED then
       yandexads.load_interstitial('R-M-DEMO-interstitial')
    end

    if message_id == yandexads.MSG_INTERSTITIAL then
       if event == yandexads.EVENT_LOADED then
          yandexads.show_interstitial()
       end
    end
end
```


## REWARDED

```lua
local function listener(self, message_id, message)
    if message_id == yandexads.MSG_ADS_INITED then
       yandexads.load_rewarded('R-M-DEMO-rewarded-client-side-rtb')
    end

    if message_id == yandexads.MSG_REWARDED then
       if event == yandexads.EVENT_LOADED then
          yandexads.show_rewarded()
       end
    end
end
```
