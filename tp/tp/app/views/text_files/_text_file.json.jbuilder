json.extract! text_file, :id, :name, :content, :created_at, :updated_at
json.url text_file_url(text_file, format: :json)
