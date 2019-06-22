Rails.application.routes.draw do
  resources :rsas
  resources :rsas do
    resources :decrypt_messages
  end
  resources :rsas do
    resources :encrypt_messages
  end
  # For details on the DSL available within this file, see http://guides.rubyonrails.org/routing.html
end
