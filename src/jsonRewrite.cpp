#include "jsonRewrite.hpp"

namespace rewrite
{

	std::string toStyledStringRewrite(Json::Value input)
	{
		Json::StreamWriterBuilder builder;
		builder.settings_["emitUTF8"] = true; //非UTF8编码填true
		std::string out = input.hasComment(Json::CommentPlacement::commentBefore) ? "\n" : "";
		out += Json::writeString(builder, input);
		out += '\n';

		return out;
	}
}