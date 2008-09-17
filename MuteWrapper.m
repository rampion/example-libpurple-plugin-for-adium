#import "MuteWrapper.h"

@implementation MuteWrapper
- (void) installLibpurplePlugin
{
}
- (void) loadLibpurplePlugin
{ 
    purple_init_mute_plugin();
}
@end