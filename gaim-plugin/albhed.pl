#
#
#
#

use Gaim;

%PLUGIN_INFO = (
	perl_api_version 	=> 2,
	name			=> "Ab Plug",
	version			=> "0.1",
	summary			=> "Ab Plug is text subsitution plugin that changes english text into Al Bhed.",
	description		=> "Ab Plug calls the program abtranslate to translate from english into the fictional language of Al Bhed found in Final Fantasy games.",
	author			=> "Josh Magee<liquidchile\@liquidchile.net",
	url			=> "http://liquidchile.net",

	load			=> "plugin_load",
	unload			=> "plugin_unload",
);


sub translate {
	#get message parts
	my $account = $_[0];
	my $who     = $_[1];
	my $im	    = $_[2];
	my $flags   = $_[3];



sub plugin_init {
	return %PLUGIN_INFO;
}

sub plugin_load {
	my $plugin = shift;
}

sub plugin_unload {
	my $plugin = shift;
}
