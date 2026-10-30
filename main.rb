require 'net/http'
require 'json'
require 'uri'

token = ENV.fetch('BOT_TOKEN')
base = "https://api.telegram.org/bot#{token}/"
offset = 0

loop do
  begin
    url = URI("#{base}getUpdates?timeout=25&offset=#{offset}")
    response = Net::HTTP.start(
      url.host, url.port, use_ssl: true, read_timeout: 35
    ) { |http| http.get(url.request_uri) }

    JSON.parse(response.body).fetch('result', []).each do |update|
      offset = update['update_id'] + 1
      message = update['message']
      next unless message && message['text']

      reply = case message['text']
              when '/start'
                'Welcome to my Ruby bot!'
              when '/help'
                'Commands: /start, /help, /about'
              when '/about'
                'I am a Telegram bot written in Ruby.'
              else
                'Unknown command. Send /help.'
              end

      send_url = URI("#{base}sendMessage")
      request = Net::HTTP::Post.new(send_url)
      request.set_form_data(
        chat_id: message.dig('chat', 'id'),
        text: reply
      )

      Net::HTTP.start(send_url.host, send_url.port, use_ssl: true) do |http|
        http.request(request)
      end
    end
  rescue StandardError => e
    warn e.message
    sleep 2
  end
end
