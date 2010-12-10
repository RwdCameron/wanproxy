#include <event/event_callback.h>

#include <io/pipe/pipe.h>

#include <xcodec/xcodec.h>
#include <xcodec/xcodec_decoder.h>
#include <xcodec/xcodec_decoder_pipe.h>
#include <xcodec/xcodec_encoder.h>

XCodecDecoderPipe::XCodecDecoderPipe(XCodec *codec)
: PipeSimple("/xcodec/decoder/pipe"),
  decoder_()
{
	(void)codec;
}

XCodecDecoderPipe::~XCodecDecoderPipe()
{ }

bool
XCodecDecoderPipe::process(Buffer *out, Buffer *in)
{
	return (decoder_.decode(out, in));
}
